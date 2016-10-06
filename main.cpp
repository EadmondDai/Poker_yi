#include <iostream>
#include <string>
#include <vector>
#include "cardlist.h"
#include "cardlist_test.h"
#include "player.h"

using namespace std;

int main(){

    CardListTest::test();

    // setup rand
    srand(time(nullptr));

    Player p;
    p.showDeck();

    return 0;
}
