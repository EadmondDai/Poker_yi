#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include <cassert>
#include <iostream>
#include "player.h"

class PlayerTest{
public:
    static void test(){
        PlayerTest::draw_a_card_test();
        PlayerTest::swap_a_card_test();
        cout<<"[PlayerTest]: All Tests OK!!!"<<endl;
    }
    static void draw_a_card_test(){
        Player* p=new Player();
        for(int i=0;i<5;i++){
            assert(p->hand->length()==i);
            assert(p->deck->length()==52-i);
            p->draw_a_card();
        }
        delete p;
    }
    static void swap_a_card_test(){
        Player* p=new Player();
        for(int i=0;i<5;i++){
            p->draw_a_card();
        }
        Card* hand0=p->hand->at(0);
        Card* deck0=p->deck->at(0);
        p->swap_a_card(0,0);
        assert(*p->hand->at(0)==*deck0 && *p->deck->at(0)==*hand0);
        delete p;
    }
};

#endif // PLAYER_TEST_H
