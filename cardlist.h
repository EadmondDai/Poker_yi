#ifndef CARDLIST_H
#define CARDLIST_H

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Card{
    char suit;      // {'S','H','C','D'}
    int value;      // [1,13]
    Card* next;
    bool operator < (const Card& c) const {
        // judge by value
        if(this->value<c.value)
            return true;
        else if(this->value>c.value)
            return false;
        // if the values are the same, then we judge by suit
        return this->suit<c.suit;
    }
    bool operator > (const Card& c) const {
        if(this->value>c.value)
            return true;
        else if(this->value<c.value)
            return false;
        return this->suit>c.suit;
    }
    void operator = (const Card& c) {
        suit=c.suit;
        value=c.value;
    }
    bool operator == (const Card& c) const {
        return this->suit==c.suit && this->value==c.value;
    }
    friend ostream& operator << (ostream& out, const Card& c){
        string values[]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
        out<<c.suit<<values[c.value]<<" ";
        if(c.value!=10)
            out<<" ";
        return out;
    }
};

class CardList{
public:
    CardList(bool isCardPool=true) : head(nullptr) {
        if(!isCardPool)
            return;
        char typeNames[]={'S','H','C','D'};
        Card* p=nullptr;
        for(int s=0;s<4;s++){
            for(int v=1;v<=13;v++){
                Card* card=new Card({typeNames[s],v,nullptr});
                if(!p){
                    p=head=card;
                }else{
                    p->next=card;
                    p=p->next;
                }
            }
        }
    }
    ~CardList(){
        vector<Card*> temp;
        for(Card* p=head;p;p=p->next){
            temp.push_back(p);
        }
        for(Card* p : temp)
            delete p;
        head=nullptr;
    }
public:
    void append(Card* card){
        if(!head)
            head=card;
        else{
            Card* p=head;
            while(p->next)
                p=p->next;
            p->next=card;
        }
        card->next=nullptr;
    }

    Card* at(int n){
        assert(n<length());
        Card* p=head;
        for(int i=0;i<n;i++,p=p->next)
            ;
        return p;
    }

    int containsSuit(char suit){
        int count=0;
        for(Card* p=head;p;p=p->next)
            if(p->suit==suit)
                count++;
        return count;
    }

    int containsValue(int value){
        int count=0;
        for(Card* p=head;p;p=p->next)
            if(p->value==value)
                count++;
        return count;
    }

    bool isEmpty() const{
        return head==nullptr;
    }

    int length() const {
        int result=0;
        for(Card* p=head;p;p=p->next)
            result++;
        return result;
    }

    Card* remove(Card* card){
        if(!card){
            cout<<"***remove(): do NOT remove a NULL card"<<endl;
            return nullptr;
        }
        if(!head){
            cout<<"***remove(): head is empty!!"<<endl;
            return nullptr;
        }
        // head or not
        if(head==card){
            head=card->next;
            card->next=nullptr;
            return card;
        }else{
            for(Card* p=head;p->next;p=p->next){
                if(p->next==card){
                    p->next=card->next;
                    card->next=nullptr;
                    return card;
                }
            }
            // fail
            cout<<"***remove(): can NOT find card:"<<card<<endl;
            return nullptr;
        }        
    }

    void report(){
        int len=length();
        cout<<"=== Cards number is "<<len<<" ==="<<endl;
        for(int i=0;i<len/20+1;i++){
            for(int j=0;j<20;j++){
                int index=i*20+j;
                if(index>=len)
                    break;
                cout<<setiosflags(ios::left)<<"#"<<setw(3)<<index;
            }
            cout<<endl;
            for(int j=0;j<20;j++){
                int index=i*20+j;
                if(index>=len)
                    break;
                cout<<*at(index);
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void sort() {
        int len=length();
        for(int i=1;i<len;i++){
            Card temp=*at(i);
            int j=i-1;
            for(;j>=0 && *at(j)>temp;j--)
                *at(j+1)=*at(j);
            *at(j+1)=temp;
        }
    }

private:
    Card* head;
};

#endif // CARDLIST_H
