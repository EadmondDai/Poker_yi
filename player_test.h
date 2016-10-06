#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include <cassert>
#include <iostream>
#include "player.h"

class PlayerTest{
public:
    static void test(){
        PlayerTest::draw_a_card_test();
        cout<<"[PlayerTest]: All Tests OK!!!"<<endl;
    }
    static void draw_a_card_test(){
        Player* p=new Player();
        for(int i=0;i<5;i++){
            assert(p->hand->length()==i);
            assert(p->deck->length()==52-i);
            p->draw_a_card();
        }
        for(int i=4;i>=0;i--){
            p->hand->remove(p->hand->at(i));
        }
        delete p;
    }
};

#endif // PLAYER_TEST_H
