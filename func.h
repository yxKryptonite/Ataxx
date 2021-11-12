//
// Created by kuangyuxuan on 2021/11/11.
//

#ifndef ATAXX_FUNC_H
#define ATAXX_FUNC_H

void showMenu();
void makeEmptyBoard(); // abolished
bool isIllegal(int chessLayout[8][8], int x, int y, int state, int ox, int oy);
void refreshLayout(int chessLayout[8][8], int x, int y, int state, int ox, int oy, int& playercnt, int& comcnt);
void player(int chessLayout[8][8], int& playercnt, int& comcnt);
void computer(int chessLayout[8][8], int& playercnt, int& comcnt);
void showBoard(int chessLayout[8][8], int playercnt, int comcnt);
void __init__(int chessLayout[8][8]);

#endif //ATAXX_FUNC_H
