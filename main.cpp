#include <iostream>
#include "func.h"
using namespace std;
int chessLayout[8][8] = {0};
int playercnt = 2, comcnt = 2;

int main() {
    char c;
    showMenu();
    cin >> c;
    __init__(chessLayout);
    showBoard(chessLayout, playercnt, comcnt);
    //makeEmptyBoard();
    player(chessLayout, playercnt, comcnt);
    showBoard(chessLayout, playercnt, comcnt);
    return 0;
}
