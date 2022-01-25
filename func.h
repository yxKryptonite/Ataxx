//
// Created by kuangyuxuan on 2021/11/11.
//

#ifndef ATAXX_FUNC_H
#define ATAXX_FUNC_H

void showMenu();
void showPause();
bool isWithin(int chessLayout[8][8], int ox, int oy, int state);
bool isLegal(int chessLayout[8][8], int x, int y, int ox, int oy);
void refreshLayout(int chessLayout[8][8], int x, int y, int state, int ox, int oy, int& playercnt, int& comcnt);
bool isEnd(int chessLayout[8][8], int state);
std::string player(int chessLayout[8][8], int& playercnt, int& comcnt, int& quit, int mode);
std::string op_player(int chessLayout[8][8], int& playercnt, int& comcnt, int& quit, int mode);
std::string computer_Easy(int chessLayout[8][8], int& playercnt, int& comcnt);
std::string computer_Normal(int chessLayout[8][8], int& playercnt, int& comcnt);
void com_easy_part(int chessLayout[8][8], int key_info[10], int& playercnt, int& comcnt, int state);
std::string computer_Hard(int chessLayout[8][8], int& playercnt, int& comcnt);
std::string computer_Devil(int chessLayout[8][8], int& playercnt, int& comcnt);
void showBoard(int chessLayout[8][8], int playercnt, int comcnt, std::string mode, int state, std::string info);
void __init__(int chessLayout[8][8]);
void PVP_MODE(int chessLayout[8][8], int playercnt, int comcnt, int sequence);
void PVE_MODE_EASY(int chessLayout[8][8], int playercnt, int comcnt);
void PVE_MODE_NORMAL(int chessLayout[8][8], int playercnt, int comcnt);
void PVE_MODE_HARD(int chessLayout[8][8], int playercnt, int comcnt);
void PVE_MODE_DEVIL(int chessLayout[8][8], int playercnt, int comcnt);
void saveRecordFile(int chessLayout[8][8], int playercnt, int comcnt, int mode, int sequence);
void loadRecordFile(int chessLayout[8][8], int& playercnt, int& comcnt, int& mode, int& sequence);
void aboutMe();
void showRules();
void showVictory();
void showDefeat();
void showBlackWin();
void showWhiteWin();
bool canMove(int chessLayout[8][8], int ox, int oy);
int count_matrix(int chessLayout[8][8], int state);

int evaluate(int playercnt, int comcnt);
void copy(int chessLayout[8][8], int tmpLayout[8][8], int& playercnt, int& comcnt, int& tmpPlayer, int& tmpCom);
void resume(int chessLayout[8][8], int tmpLayout[8][8], int& playercnt, int& comcnt, int& tmpPlayer, int& tmpCom);
void minmax(int chessLayout[8][8], int depth, int playercnt, int comcnt);
int Min(int chessLayout[8][8], int depth, int playercnt, int comcnt);
int Max(int chessLayout[8][8], int depth, int playercnt, int comcnt);
bool canMoveForMinMax(int chessLayout[8][8], int state);

#endif //ATAXX_FUNC_H
