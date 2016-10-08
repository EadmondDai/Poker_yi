#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__, __LINE__ )
#define new DBG_NEW
#endif
#endif

#include <iostream>
#include <string>
#include <vector>
#include "cardlist.h"
#include "cardlist_test.h"
#include "player.h"
#include "player_test.h"

using namespace std;

int main(){

//    CardListTest::test();
//    PlayerTest::test();


    // setup rand
    srand(time(nullptr));

    Player* p=new Player;
    p->start();
	delete p;

	_CrtDumpMemoryLeaks();

    return 0;
}
