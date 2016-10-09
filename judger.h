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
    static pair<string,int> judge(CardList* list){

        // Royal Flush (Royal Straight Flush)
        if(isRoyal(list) && isFlush(list) && isStraight(list))
            return {"Royal Flush", 800};

        // Straight Flush
        if(isStraight(list) && isFlush(list))
            return {"Straight Flush", 50};

        // 4 of a kind
        if(is4(list))
            return {"4 of a Kind", 25};

        // Full House
        if(is3(list) && n2(list)==1)
            return {"Full House", 9};

        // Flush (all in one kind)
        if(isFlush(list))
            return {"Flush", 6};

        if(isStraight(list))
            return {"Straight", 4};

        // 3 of a kind
        if(is3(list))
            return {"3 of a Kind", 3};

        // 2 pair
        if(n2(list)==2)
            return {"2 Pair", 2};

        // 1 J+ pair
        if(is1(list))
            return {"1 J+ Pair", 1};

        return {"nothing", 0};
    }
    static bool isRoyal(CardList* list){
        return list->containsValue(10) && list->containsValue(11) && list->containsValue(12) && list->containsValue(13) && list->containsValue(1);
    }
    static bool isFlush(CardList* list){
        return list->containsSuit('S')==5 || list->containsSuit('H')==5 || list->containsSuit('C')==5 || list->containsSuit('D')==5;
    }
    static bool isStraight(CardList* list){
        list->sort();
		if(isRoyal(list)) return true;
		//if (list->at(4)->value - list->at(0)->value != 4) return false;
		int baseValue = list->at(0)->value;
		for (int i = 1; i < 5; i++)
			if (list->at(i)->value != baseValue + i)
				return false;
		return true;
    }
    static bool is4(CardList* list){
        for(int i=1;i<13;i++)
            if(list->containsValue(i)==4)
                return true;
        return false;
    }
    static bool is3(CardList* list){
        for(int i=1;i<=13;i++)
            if(list->containsValue(i)==3)
                return true;
        return false;
    }
    static int n2(CardList* list){
        int pairs=0;
        for(int i=1;i<=13;i++)
            if(list->containsValue(i)==2)
                pairs++;
        return pairs;
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
