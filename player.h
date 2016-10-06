#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "cardlist.h"
#include "judger.h"

using namespace std;

class PlayerTest;
class Player{
    friend class PlayerTest;
public:
    Player():money(10){
        deck=new CardList(true);
        hand=new CardList(false);
        discard=new CardList(false);
    }
    ~Player() {
        delete deck;
        delete hand;
        delete discard;
    }

    pair<string,int> oneRound(){
        showMoney();
        money--;
        cout<<"You payed $1 for this round!"<<endl;
        showMoney();
        // start and draw 5 cards
        while(true){
            string cmd=get_cmd({"start","deck","exit"});
            if(cmd=="exit")
                return {"exit",0};
            if(run_cmd(cmd)=="next")
                break;  // proceed
        }
        showCards();
        // change cards
        while(true){
            string cmd=get_cmd({"keep","deck","swap","exit"});
            if(cmd=="exit")
                return {"exit",0};
            if(run_cmd(cmd)=="next")
                break;  // proceed
        }
        showCards();
        // judge!
        int winMoney=Judger::judge(hand);
        if(winMoney==0)
            return {"",0};
        else
            return {"win", winMoney};
    }

    string get_cmd(vector<string> valid){
        cout<<"Input command, choose from: {";
        for(const string s : valid)
            cout<<s<<",";
        cout<<"} ";
        string cmd;
        while(true){
            cin>>cmd;
            // command is valid
            if(find(valid.begin(),valid.end(),cmd)!=valid.end())
                break;
        }
        return cmd;
    }

    string run_cmd(string cmd){
        if(cmd=="start"){
            cmd_start();
            return "next";
        }else if(cmd=="deck"){
            cmd_deck();
        }else if(cmd=="swap"){
            cout<<"*** swap is for DEBUG! Only Walt and Yi can use that."<<endl;
            cmd_swap();
        }else if(cmd=="keep"){
            cmd_keep();            
            return "next";
        }
        return "";
    }

    void cmd_deck(){
        deck->report();
    }
    void cmd_start(){
        // draw 5 cards
        for(int i=0;i<5;i++){
            draw_a_card();
        }
    }
    void cmd_swap(){
        cout<<"To debug-swap, please enter as follow: 1,20, which means to swap your #1 card with deck's #20 card."<<endl;
        cout<<"Please notice that since we are debugging, you MUST input correctly."<<endl;
        // input
        string cmd;
        int myIndex=0, deckIndex=0;
        while(true){
            cin>>cmd;
            // get indice
            myIndex=cmd[0]-'0';
            deckIndex=stoi(cmd.substr(2,2));
            // check
            if(myIndex>=0 && myIndex<5 && deckIndex>=0 && deckIndex<deck->length())
                break;
        }
        swap_a_card(myIndex, deckIndex);
    }
    void cmd_keep(){
        cout<<"Please input card indice to tell me what cards to keep, e.g. 013:"<<endl;
        hand->report();
        // get good input
        string kp;
        bool keepCards[]={false,false,false,false,false};
        while(true){
            cin>>kp;
            bool goodInput=true;
            for(int i=0;i<kp.length();i++){
                if(kp[i]<'0' || kp[i]>'9'){
                    cout<<"*** please input numbers!"<<endl;
                    goodInput=false;
                    break;
                }
            }
            if(goodInput)
                break;
        }

        // get cards to keep
        int keepCount=0;
        for(int i=0;i<kp.length();i++){
            int keepIndex=char(kp[i])-char('0');
            assert(keepIndex>=0 && keepIndex<5);
            keepCards[keepIndex]=true;
            keepCount++;
        }        
        // discard cards
        for(int i=4;i>=0;i--){
            if(!keepCards[i]){
                Card* toRemove=hand->remove(hand->at(i));
                discard->append(toRemove);
            }
        }
        // draw new cards
        int discardCount=5-keepCount;
        for(int i=0;i<discardCount;i++)
            draw_a_card();
        cout<<"After exchanging...."<<endl;
        hand->report();
    }

    void draw_a_card(){
        // if there's no card in deck, then just swap discard with deck
        if(deck->length()==0){
            cout<<"There's no card in deck, so let's rebuild it by swapping: discard <===> deck!"<<endl;
            CardList* temp=deck;
            deck=discard;
            discard=temp;
        }
        // there is >=1 card in deck now!
        int index=rand()%deck->length();
        Card* one=deck->remove(deck->at(index));
        hand->append(one);
        hand->sort();
    }
    void swap_a_card(int handIndex, int deckIndex){
        Card* handRemove=hand->remove(hand->at(handIndex));
        Card* deckRemove=deck->remove(deck->at(deckIndex));
        hand->append(deckRemove);
        deck->append(handRemove);
        hand->sort();
        deck->sort();
    }

    void showMoney(){
        cout<<"Now you have: $"<<money<<endl;
    }
    void showCards(){
        cout<<"Your hand cards:";
        hand->report();
    }
    void showDeck(){
        cout<<"Your deck cards:";
        deck->report();
    }

    void start(){
        while(true){
            // go one round
            pair<string,int> result=oneRound();

            // player wants to exit the game
            if(result.first=="exit")
                return;

            // otherwise:
            if(result.first=="win"){
                money+=result.second;
                showMoney();
            }
            // hand ==> discard
            for(int i=0;i<5;i++){
                Card* one=hand->remove(hand->at(0));
                discard->append(one);
            }
            // start another round
            cout<<"Now, let's start another round!"<<endl;
        }
    }

private:
    int money;
    CardList* deck;
    CardList* hand;
    CardList* discard;
};

#endif // PLAYER_H
