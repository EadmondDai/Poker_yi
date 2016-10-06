#ifndef JUDGER_H
#define JUDGER_H

#include "cardlist.h"

class Judger{
public:
    // Royal Flush: S10 SJ SQ SK SA, 800
    // Straight Flush: H3 H4 H5 H6 H7, 50
    // 4 of a Kind: S2 S3 S8 S9 H1, 25
    // Full House: 4 4 4 6 6, 9
    // Flush: H H H H H, 6
    // Straight: 3 4 5 6 7, 4
    // 3 of a Kind: 3
    // 2 Pair: 2
    // 1 J+ Pair: 1
    static int judge(CardList* list){

        // Royal Flush (Royal Straight Flush)
        if(isRoyal(list) && isFlush(list) && isStraight(list))
            return 800;

        // Straight Flush
        if(isStraight(list) && isFlush(list))
            return 50;

        // 4 of a kind
        if(is4(list))
            return 25;

        // Full House
        if(is3(list) && n2(list))
            return 9;

        // Flush (all in one kind)
        if(isFlush(list))
            return 6;

        // 3 of a kind
        if(is3(list))
            return 3;

        // 2 pair
        if(n2(list)==2)
            return 2;

        // 1 J+ pair
        if(is1(list))
            return 1;

        return 0;
    }
    static bool isRoyal(CardList* list){
        return list->containsValue(10) && list->containsValue(11) && list->containsValue(12) && list->containsValue(13) && list->containsValue(1);
    }
    static bool isFlush(CardList* list){
        return list->containsSuit('S')==5 || list->containsSuit('H')==5 || list->containsSuit('C')==5 || list->containsSuit('D')==5;
    }
    static bool isStraight(CardList* list){
        list->sort();
        return isRoyal(list) || list->at(4)->value - list->at(0)->value == 4;
    }
    static bool is4(CardList* list){
        return list->containsSuit('S')==4 || list->containsSuit('H')==4 || list->containsSuit('C')==4 || list->containsSuit('D')==4;
    }
    static bool is3(CardList* list){
        return list->containsSuit('S')==3 || list->containsSuit('H')==3 || list->containsSuit('C')==3 || list->containsSuit('D')==3;
    }
    static int n2(CardList* list){
        char suit[]={'S','H','C','D'};
        int count=0;
        for(int i=0;i<4;i++)
            if(list->containsSuit(suit[i])==2)
                count++;
        return count;
    }
    static bool is1(CardList* list){
        int value[]={11,12,13,1};
        for(int i=0;i<4;i++)
            if(list->containsValue(value[i])==2)
                return true;
        return false;
    }
};

#endif // JUDGER_H
