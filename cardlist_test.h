#ifndef CARDLIST_TEST_H
#define CARDLIST_TEST_H

#include <cassert>
#include "cardlist.h"

class CardListTest{
public:
    static void structTest(){
        assert(Card({'S',12,nullptr})>Card({'C',12,nullptr}));
        assert(Card({'S',12,nullptr})>Card({'S',1,nullptr}));
        assert(Card({'S',1,nullptr})<Card({'S',12,nullptr}));
        assert(Card({'C',1,nullptr})<Card({'H',1,nullptr}));
    }
    static void conTest(){
        CardList* list=new CardList(true);
        assert(list->length()==52);
        assert(list->containsSuit('S')==13);
        for(int i=1;i<=13;i++)
            assert(list->containsValue(i)==4);
        assert(*list->at(0) == Card({'S',1,nullptr}));
        list->sort();
        assert(Card({'S',13,nullptr}) == *list->at(51));
        list->remove(list->at(0));
        list->remove(list->at(50));
        assert(list->length()==50);
        assert(Card({'D',1,nullptr}) == *list->at(0));
        assert(Card({'H',13,nullptr}) == *list->at(49));
        assert(list->length()==50);
        for(int i=0;i<49;i++)
            list->remove(list->at(0));
        assert(list->length()==1);
        assert(!list->isEmpty());
        list->remove(list->at(list->length()-1));
        assert(list->isEmpty());
        assert(list->containsSuit('H')==0);
        assert(list->containsValue(13)==0);
    }

    static void test(){
        structTest();
        conTest();
        cout<<"All tests OK!!!"<<endl;
    }
};

#endif // CARDLIST_TEST_H
