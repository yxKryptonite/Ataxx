//
// Created by kuangyuxuan on 2021/11/11.
//

#include <iostream>
#include "func.h"
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <map>
#include <string>

using namespace std;
#define E 0 // E refers to empty
#define P 1 // P refers to player
#define C 2 // C refers to computer or opponent player (pvp mode)

int best_move[10] = {0};

// show the starting menu
void showMenu() {
    system("clear");
    printf("##################################\n");
    printf("##       Welcome to Ataxx!      ##\n");
    printf("##                              ##\n");
    printf("##   Please make your choice:   ##\n");
    printf("##          1. PVP              ##\n");
    printf("##          2. PVE_EASY         ##\n");
    printf("##          3. PVE_NORMAL       ##\n");
    printf("##          4. PVE_HARD         ##\n");
    printf("##          5. LOAD             ##\n");
    printf("##          6. RULES            ##\n");
    printf("##          7. ABOUTME          ##\n");
    printf("##          8. EXIT             ##\n");
    printf("##                              ##\n");
    printf("##          Have Fun!           ##\n");
    printf("##################################\n");
    printf("##         (9. DEVIL)           ##\n");
    printf("##################################\n");
}

// show the pausing menu
void showPause() {
    system("clear");
    printf("##################################\n");
    printf("##            PAUSING...        ##\n");
    printf("##                              ##\n");
    printf("##   Please make your choice:   ##\n");
    printf("##          1. RESUME           ##\n");
    printf("##          2. SAVE             ##\n");
    printf("##          3. EXIT             ##\n");
    printf("##                              ##\n");
    printf("##################################\n");
}

// judge whether the ox & oy is legal (to prevent the segmentation fault)
bool isWithin(int chessLayout[8][8], int ox, int oy, int state) {
//    if (ox == 0 && oy == 0)
//        return true;
    if (ox < 1 || ox > 7)
        return false;
    if (oy < 1 || oy > 7)
        return false;
    if (chessLayout[ox][oy] != state)
        return false;
    return true;
}

// judge the movement (state refers to player or computer, ox refers to original x, oy be the same)
bool isLegal(int chessLayout[8][8], int x, int y, int ox, int oy) {
    if (x < 1 || x > 7)
        return false;
    if (y < 1 || y > 7)
        return false;
    if (x == ox && y == oy)
        return false;
    if (chessLayout[x][y] != E)
        return false;
    int dis_x = abs(x - ox);
    int dis_y = abs(y - oy);
    if (dis_x <= 2 && dis_y <= 2)
        return true;
    else
        return false;
}

// change the array "chessLayout"
void refreshLayout(int chessLayout[8][8], int x, int y, int state, int ox, int oy, int& playercnt, int& comcnt) {
    int enemy;
    if (state == P)
        enemy = C;
    else if (state == C)
        enemy = P;
    int dis_x = abs(x - ox);
    int dis_y = abs(y - oy);
    if (dis_x <= 1 && dis_y <= 1) {
        if (state == P) {
            chessLayout[x][y] = state;
            playercnt++;
        }
        else if (state == C) {
            chessLayout[x][y] = state;
            comcnt++;
        }
    }
    else {
        chessLayout[ox][oy] = E;
        chessLayout[x][y] = state;
    }
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (chessLayout[i][j] == enemy) {
                chessLayout[i][j] = state;
                if (state == P) {
                    playercnt++;
                    comcnt--;
                }
                else if (state == C) {
                    comcnt++;
                    playercnt--;
                }
            }
        }
    }
}

//judge whether the player/computer could move its chessman
bool isEnd(int chessLayout[8][8], int state) {
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == state) {
                for (int k = i - 2; k <= i + 2; ++k) {
                    for (int l = j - 2; l <= j + 2; ++l) {
                        if (isLegal(chessLayout, k, l, i, j)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}


// the player makes action (from to-move chessman to goal position)
// quit: 0 refers to continue, 1 refers to quit
// the function player records the *mode* of the Ataxx game, op_player be the same
// the returned string keeps the chessman movement, op_player & computer be the same
// P.S. the computer won't pause
string player(int chessLayout[8][8], int& playercnt, int& comcnt, int& quit, int mode) {
    string s;
    if (isEnd(chessLayout, P)) {
        return "END";
    }
    string sMode;
    if (mode == 1)
        sMode = "PVP";
    else if (mode == 2)
        sMode = "PVE_EASY";
    else if (mode == 3)
        sMode = "PVE_NORMAL";
    else if (mode == 4)
        sMode = "PVE_HARD";
    else if (mode == 5)
        sMode = "PVE_DEVIL";
    int x, y, ox, oy;
    printf("Please input the coordinates of your to-move chessman (BLACK)\n(input 0 & 0 to pause)\n");
    printf("X axis: ");
    cin >> ox;
    printf("Y axis: ");
    cin >> oy;
    while (ox == 0 && oy == 0) {
        int i;
        showPause();
        cin >> i;
        switch (i) {
            case 1:
                system("clear");
                cout << "Welcome back!\n3\n";
                sleep(1);
                cout << "2\n";
                sleep(1);
                cout << "1\n";
                sleep(1);
                showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
                printf("Please input the coordinates of your to-move chessman (BLACK)\n(input 0 & 0 to pause)\n");
                printf("X axis: ");
                cin >> ox;
                printf("Y axis: ");
                cin >> oy;
                break;
            case 2:
                saveRecordFile(chessLayout, playercnt, comcnt, mode, 1);
                cout << "SUCCESSFULLY SAVED!\n";
                cout << "PRESS ANY BUTTON TO CONTINUE...\n";
                getchar();
                getchar();
                break;
            case 3:
                quit = 1;
                return "QUIT";
            default:
                cout << "DEVELOPING...\n";
                sleep(1);
                break;
        }
    }
    while (!isWithin(chessLayout, ox, oy, P) || !canMove(chessLayout, ox, oy)) {
        printf("ILLEGAL!!! Please input the coordinates of your to-move chessman again\n");
        printf("X axis: ");
        cin >> ox;
        printf("Y axis: ");
        cin >> oy;
    }
    printf("Please input the coordinates of your goal position (BLACK)\n");
    printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
    printf("X axis: ");
    cin >> x;
    printf("Y axis: ");
    cin >> y;
    while (x == 0 && y == 0) {
        int i;
        showPause();
        cin >> i;
        switch (i) {
            case 1:
                system("clear");
                cout << "Welcome back!\n3\n";
                sleep(1);
                cout << "2\n";
                sleep(1);
                cout << "1\n";
                sleep(1);
                showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
                printf("Please input the coordinates of your goal position (BLACK)\n");
                printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
                printf("X axis: ");
                cin >> x;
                printf("Y axis: ");
                cin >> y;
                break;
            case 2:
                saveRecordFile(chessLayout, playercnt, comcnt, mode, 1);
                cout << "SUCCESSFULLY SAVED!\n";
                cout << "PRESS ANY BUTTON TO CONTINUE...\n";
                getchar();
                getchar();
                break;
            case 3:
                quit = 1;
                return "QUIT";
            default:
                cout << "DEVELOPING...\n";
                sleep(1);
                break;
        }
    }
    while (!isLegal(chessLayout, x, y, ox, oy)) {
        printf("ILLEGAL!!! Please move your chess again\n");
        printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
        printf("Your x axis: ");
        cin >> x;
        printf("Your y axis: ");
        cin >> y;
    }
    refreshLayout(chessLayout, x, y, P, ox, oy, playercnt, comcnt);
    s.append(1, char(x + '0'));
    s.append(1, char(y + '0'));
    s.append(1, char(ox + '0'));
    s.append(1, char(oy + '0'));
    return s;
}

// the opponent player makes action (pvp mode)
// uses the comcnt and so on
string op_player(int chessLayout[8][8], int& playercnt, int& comcnt, int& quit, int mode) {
    string s;
    if (isEnd(chessLayout, C)) {
        return "END";
    }
    string sMode;
    if (mode == 1)
        sMode = "PVP";
    else if (mode == 2)
        sMode = "PVE_EASY";
    else if (mode == 3)
        sMode = "PVE_NORMAL";
    else if (mode == 4)
        sMode = "PVE_HARD";
    int x, y, ox, oy;
    printf("Please input the coordinates of your to-move chessman (WHITE)\n(input 0 & 0 to pause)\n");
    printf("X axis: ");
    cin >> ox;
    printf("Y axis: ");
    cin >> oy;
    while (ox == 0 && oy == 0) {
        int i;
        showPause();
        cin >> i;
        switch (i) {
            case 1:
                system("clear");
                cout << "Welcome back!\n3\n";
                sleep(1);
                cout << "2\n";
                sleep(1);
                cout << "1\n";
                sleep(1);
                showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
                printf("Please input the coordinates of your to-move chessman (WHITE)\n(input 0 & 0 to pause)\n");
                printf("X axis: ");
                cin >> ox;
                printf("Y axis: ");
                cin >> oy;
                break;
            case 2:
                saveRecordFile(chessLayout, playercnt, comcnt, mode, 2);
                cout << "SUCCESSFULLY SAVED!\n";
                cout << "PRESS ANY BUTTON TO CONTINUE...\n";
                getchar();
                getchar();
                break;
            case 3:
                quit = 1;
                return "QUIT";
            default:
                cout << "DEVELOPING...\n";
                sleep(1);
                break;
        }
    }
    while (!isWithin(chessLayout, ox, oy, C) || !canMove(chessLayout, ox, oy)) {
        printf("ILLEGAL!!! Please input the coordinates of your to-move chessman again\n");
        printf("X axis: ");
        cin >> ox;
        printf("Y axis: ");
        cin >> oy;
    }
    printf("Please input the coordinates of your goal position (WHITE)\n");
    printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
    printf("X axis: ");
    cin >> x;
    printf("Y axis: ");
    cin >> y;
    while (x == 0 && y == 0) {
        int i;
        showPause();
        cin >> i;
        switch (i) {
            case 1:
                system("clear");
                cout << "Welcome back!\n3\n";
                sleep(1);
                cout << "2\n";
                sleep(1);
                cout << "1\n";
                sleep(1);
                showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
                printf("Please input the coordinates of your goal position (WHITE)\n");
                printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
                printf("X axis: ");
                cin >> x;
                printf("Y axis: ");
                cin >> y;
                break;
            case 2:
                saveRecordFile(chessLayout, playercnt, comcnt, mode, 1);
                cout << "SUCCESSFULLY SAVED!\n";
                cout << "PRESS ANY BUTTON TO CONTINUE...\n";
                getchar();
                getchar();
                break;
            case 3:
                quit = 1;
                return "QUIT";
            default:
                cout << "DEVELOPING...\n";
                sleep(1);
                break;
        }
    }
    while (!isLegal(chessLayout, x, y, ox, oy)) {
        printf("ILLEGAL!!! Please move your chess again\n");
        printf("Hint: your to-move chessman is (%d, %d)\n(input 0 & 0 to pause)\n", ox, oy);
        printf("Your x axis: ");
        cin >> x;
        printf("Your y axis: ");
        cin >> y;
    }
    refreshLayout(chessLayout, x, y, C, ox, oy, playercnt, comcnt);
    s.append(1, char(x + '0'));
    s.append(1, char(y + '0'));
    s.append(1, char(ox + '0'));
    s.append(1, char(oy + '0'));
    return s;
}

// the computer makes action automatically with the very easy GREEDY algorithm
string computer_Easy(int chessLayout[8][8], int& playercnt, int& comcnt) {
    string info;
    int maximum = comcnt;
    int key_info[10] = {0}; // keep key information locally, 1-4 refer to x, y, ox, oy
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == C) {
                int playercnt_tmp = playercnt;
                int comcnt_tmp = comcnt;
                // copy the array
                int tmpLayout[8][8] = {0};
                for (int a = 1; a <= 7; ++a) {
                    for (int b = 1; b <= 7; ++b) {
                        tmpLayout[a][b] = chessLayout[a][b];
                    }
                }
                for (int x = i - 2; x <= i + 2; ++x) {
                    for (int y = j - 2; y <= j + 2; ++y) {
                        if (isLegal(chessLayout, x, y, i, j)) {
                            refreshLayout(chessLayout, x, y, C, i, j, playercnt_tmp, comcnt_tmp);
                            if (comcnt_tmp >= maximum) {
                                maximum = comcnt_tmp;
                                key_info[1] = x;
                                key_info[2] = y;
                                key_info[3] = i;
                                key_info[4] = j;
                            }
                            // copy the array back
                            for (int a = 1; a <= 7; ++a) {
                                for (int b = 1; b <= 7; ++b) {
                                    chessLayout[a][b] = tmpLayout[a][b];
                                }
                            }
                            playercnt_tmp = playercnt;
                            comcnt_tmp = comcnt;
                        }
                    }
                }
            }
        }
    }
    refreshLayout(chessLayout, key_info[1], key_info[2], C, key_info[3], key_info[4], playercnt, comcnt);
    info.append(1, char(key_info[1] + '0'));
    info.append(1, char(key_info[2] + '0'));
    info.append(1, char(key_info[3] + '0'));
    info.append(1, char(key_info[4] + '0'));
    return info;
}
// part of the easy computer (prototype)
void com_easy_part(int chessLayout[8][8], int key_info[10], int& playercnt, int& comcnt, int state) {
    int maximum = 0;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == state) {
                int playercnt_tmp = playercnt;
                int comcnt_tmp = comcnt;
                // copy the array
                int tmpLayout[8][8] = {0};
                for (int a = 1; a <= 7; ++a) {
                    for (int b = 1; b <= 7; ++b) {
                        tmpLayout[a][b] = chessLayout[a][b];
                    }
                }
                for (int x = i - 2; x <= i + 2; ++x) {
                    for (int y = j - 2; y <= j + 2; ++y) {
                        if (isLegal(chessLayout, x, y, i, j)) {
                            refreshLayout(chessLayout, x, y, state, i, j, playercnt_tmp, comcnt_tmp);
                            int tmp;
                            if (state == C)
                                tmp = comcnt_tmp;
                            else
                                tmp = playercnt_tmp;
                            if (tmp >= maximum) {
                                maximum = tmp;
                                key_info[1] = x;
                                key_info[2] = y;
                                key_info[3] = i;
                                key_info[4] = j;
                            }
                            // copy the array back
                            for (int a = 1; a <= 7; ++a) {
                                for (int b = 1; b <= 7; ++b) {
                                    chessLayout[a][b] = tmpLayout[a][b];
                                }
                            }
                            playercnt_tmp = playercnt;
                            comcnt_tmp = comcnt;
                        }
                    }
                }
            }
        }
    }
}

// the normal mode computer artificial intelligence, the basic principle is to reunion 3 easy mode
// computer (move 3 times & a one-layer deeper search) to find a better movement
// P.S. it seems like not so intelligent...a little bit clumsy instead...
string computer_Normal(int chessLayout[8][8], int& playercnt, int& comcnt) {
    string info;
    int playercnt_tmp = playercnt;
    int comcnt_tmp = comcnt;
    // copy the array
    int tmpLayout[8][8] = {0};
    for (int a = 1; a <= 7; ++a) {
        for (int b = 1; b <= 7; ++b) {
            tmpLayout[a][b] = chessLayout[a][b];
        }
    }
    int key_info[10] = {0};
    int key_info_local[10] = {0};
    // the first simulation by computer
    com_easy_part(chessLayout, key_info, playercnt, comcnt, C);
    refreshLayout(chessLayout, key_info[1], key_info[2], C, key_info[3], key_info[4], playercnt, comcnt);
    for (int i = 1; i <= 4; ++i)
        key_info_local[i] = key_info[i];
    // the second simulation by "computer player"
    com_easy_part(chessLayout, key_info, playercnt, comcnt, P);
    refreshLayout(chessLayout, key_info[1], key_info[2], P, key_info[3], key_info[4], playercnt, comcnt);
    // the third simulation by computer
    com_easy_part(chessLayout, key_info, playercnt, comcnt, C);
    // copy the array back
    for (int a = 1; a <= 7; ++a) {
        for (int b = 1; b <= 7; ++b) {
            chessLayout[a][b] = tmpLayout[a][b];
        }
    }
    playercnt = playercnt_tmp;
    comcnt = comcnt_tmp;
    // the real move
    if (isLegal(chessLayout, key_info[1], key_info[2], key_info_local[3], key_info_local[4])
    && chessLayout[key_info[3]][key_info[4]] == C) {
        refreshLayout(chessLayout, key_info[1], key_info[2], C, key_info_local[3], key_info_local[4], playercnt, comcnt);
        info.append(1, char(key_info[1] + '0'));
        info.append(1, char(key_info[2] + '0'));
        info.append(1, char(key_info_local[3] + '0'));
        info.append(1, char(key_info_local[4] + '0'));
        return info;
    }
    else {
        refreshLayout(chessLayout, key_info_local[1], key_info_local[2], C, key_info_local[3], key_info_local[4], playercnt, comcnt);
        info.append(1, char(key_info_local[1] + '0'));
        info.append(1, char(key_info_local[2] + '0'));
        info.append(1, char(key_info_local[3] + '0'));
        info.append(1, char(key_info_local[4] + '0'));
        return info;
    }
}


// the real real intelligent computer engine
// uses the strategy of max differences & the max matrix
string computer_Hard(int chessLayout[8][8], int& playercnt, int& comcnt) {
    string info;
    int maximum = -49;
    int maxMatrix = -49;
    int key_info[10] = {0}; // keep key information locally, 1-4 refer to x, y, ox, oy
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == C) {
                int playercnt_tmp = playercnt;
                int comcnt_tmp = comcnt;
                // copy the array
                int tmpLayout[8][8] = {0};
                for (int a = 1; a <= 7; ++a) {
                    for (int b = 1; b <= 7; ++b) {
                        tmpLayout[a][b] = chessLayout[a][b];
                    }
                }
                for (int x = i - 2; x <= i + 2; ++x) {
                    for (int y = j - 2; y <= j + 2; ++y) {
                        if (isLegal(chessLayout, x, y, i, j)) {
                            refreshLayout(chessLayout, x, y, C, i, j, playercnt_tmp, comcnt_tmp);
                            int diff = comcnt_tmp - playercnt_tmp;
                            if (diff > maximum) {
                                maximum = diff;
                                key_info[1] = x;
                                key_info[2] = y;
                                key_info[3] = i;
                                key_info[4] = j;
                                maxMatrix = count_matrix(chessLayout, C);
                            }
                            else if (diff == maximum) {
                                if (count_matrix(chessLayout, C) >= maxMatrix) {
                                    maximum = diff;
                                    key_info[1] = x;
                                    key_info[2] = y;
                                    key_info[3] = i;
                                    key_info[4] = j;
                                    maxMatrix = count_matrix(chessLayout, C);
                                }
                            }
                            // copy the array back
                            for (int a = 1; a <= 7; ++a) {
                                for (int b = 1; b <= 7; ++b) {
                                    chessLayout[a][b] = tmpLayout[a][b];
                                }
                            }
                            playercnt_tmp = playercnt;
                            comcnt_tmp = comcnt;
                        }
                    }
                }
            }
        }
    }
    refreshLayout(chessLayout, key_info[1], key_info[2], C, key_info[3], key_info[4], playercnt, comcnt);
    info.append(1, char(key_info[1] + '0'));
    info.append(1, char(key_info[2] + '0'));
    info.append(1, char(key_info[3] + '0'));
    info.append(1, char(key_info[4] + '0'));
    return info;
}

// a computer using the function deepSearch
string computer_Devil(int chessLayout[8][8], int& playercnt, int& comcnt) {
    string info;
    minmax(chessLayout, 3, playercnt, comcnt);
    refreshLayout(chessLayout, best_move[2], best_move[3], C, best_move[0], best_move[1], playercnt, comcnt);
    info.append(1, char(best_move[2] + '0'));
    info.append(1, char(best_move[3] + '0'));
    info.append(1, char(best_move[0] + '0'));
    info.append(1, char(best_move[1] + '0'));
    return info;
}

// show the chessboard according to the array "chessLayout"
// mode, state, info determines the output, providing more details
void showBoard(int chessLayout[8][8], int playercnt, int comcnt, string mode, int state, string info) {
    system("clear");
    if (mode == "PVP") {
        printf(" BLACK: %2d              ┃              WHITE: %2d", playercnt, comcnt);
    }
    else {
        printf(" YOU: %2d                ┃                BOT: %2d", playercnt, comcnt);
    }
    cout << "         mode: " << mode << endl;
    printf(" ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("      1     2     3     4     5     6     7  \n");
    printf("   ┏━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓  \n");
    printf(" 1 ┃");
    for (int i = 1; i <= 7; ++i) {
        if (chessLayout[1][i] == P) {
            printf("  ●  ┃");
        }
        else if (chessLayout[1][i] == C) {
            printf("  ○  ┃");
        }
        else {
            printf("     ┃");
        }
    }
    cout << endl;
    for (int i = 2; i <= 7; ++i) {
        printf("   ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫  \n");
        printf(" %d ┃", i);
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == P) {
                printf("  ●  ┃");
            }
            else if (chessLayout[i][j] == C) {
                printf("  ○  ┃");
            }
            else {
                printf("     ┃");
            }
        }
        cout << endl;
    }
    printf("   ┗━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┛  \n");
    if (mode == "PVP") {
        if (state == P)
            printf("BLACK MOVED THE CHESSMAN FROM (%c, %c) TO (%c, %c)\n", info[2], info[3], info[0], info[1]);
        else if (state == C)
            printf("WHITE MOVED THE CHESSMAN FROM (%c, %c) TO (%c, %c)\n", info[2], info[3], info[0], info[1]);
    }
    else if (mode == "PVE_EASY" || mode == "PVE_NORMAL" || mode == "PVE_HARD" || mode == "PVE_DEVIL") {
        if (state == P)
            printf("YOU MOVED THE CHESSMAN FROM (%c, %c) TO (%c, %c)\n", info[2], info[3], info[0], info[1]);
        else if (state == C)
            printf("COMPUTER MOVED THE CHESSMAN FROM (%c, %c) TO (%c, %c)\n", info[2], info[3], info[0], info[1]);
    }
}

// initialize the array "chessLayout"
void __init__(int chessLayout[8][8]) {
    chessLayout[1][1] = P;
    chessLayout[7][7] = P;
    chessLayout[1][7] = C;
    chessLayout[7][1] = C;
}



// Below are the basic modes of the Ataxx game:
// pvp mode, black goes first
void PVP_MODE(int chessLayout[8][8], int playercnt, int comcnt, int sequence) {
    int quit = 0;
    string sMode = "PVP";
    showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
    if (sequence == 1) {
        while (true) {
            if (!isEnd(chessLayout, P)) {
                string info = player(chessLayout, playercnt, comcnt, quit, 1);
                if (quit) {
                    return;
                }
                showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
            }
            else {
                comcnt = 49 - playercnt;
                break;
            }
            if (!isEnd(chessLayout, C)) {
                string info = op_player(chessLayout, playercnt, comcnt, quit, 1);
                if (quit) {
                    return;
                }
                showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
            }
            else {
                playercnt = 49 - comcnt;
                break;
            }
            if (playercnt == 0 || comcnt == 0)
                break;
        }
        if (playercnt > comcnt) {
            showBlackWin();
            cout << "BLACK WINS!" << endl;
        }
        else if (playercnt < comcnt) {
            showWhiteWin();
            cout << "WHITE WINS!" << endl;
        }
        cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
        getchar();
        getchar();
    }
    else if (sequence == 2) {
        while (true) {
            if (!isEnd(chessLayout, C)) {
                string info = op_player(chessLayout, playercnt, comcnt, quit, 1);
                if (quit) {
                    return;
                }
                showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
            }
            else {
                playercnt = 49 - comcnt;
                break;
            }
            if (!isEnd(chessLayout, P)) {
                string info = player(chessLayout, playercnt, comcnt, quit, 1);
                if (quit) {
                    return;
                }
                showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
            }
            else {
                comcnt = 49 - playercnt;
                break;
            }
            if (playercnt == 0 || comcnt == 0)
                break;
        }
        if (playercnt > comcnt) {
            showBlackWin();
            cout << "BLACK WINS!" << endl;
        }
        else if (playercnt < comcnt) {
            showWhiteWin();
            cout << "WHITE WINS!" << endl;
        }
        cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
        getchar();
        getchar();
    }
}

// pve easy mode, black (you) goes first
void PVE_MODE_EASY(int chessLayout[8][8], int playercnt, int comcnt) {
    int quit = 0;
    string sMode = "PVE_EASY";
    showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
    while (true) {
        if (!isEnd(chessLayout, P)) {
            string info = player(chessLayout, playercnt, comcnt, quit, 2);
            if (quit) {
                return;
            }
            showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
        }
        else {
            comcnt = 49 - playercnt;
            break;
        }
        cout << "The computer is processing...\n";
        sleep(3);
        if (!isEnd(chessLayout, C)) {
            string info = computer_Easy(chessLayout, playercnt, comcnt);
            showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
        }
        else {
            playercnt = 49 - comcnt;
            break;
        }
        if (playercnt == 0 || comcnt == 0)
            break;
    }
    if (playercnt > comcnt) {
        showVictory();
        cout << "YOU WIN!" << endl;
    }
    else if (playercnt < comcnt) {
        showDefeat();
        cout << "YOU LOSE!" << endl;
    }
    cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
    getchar();
    getchar();
}

// pve normal mode, black (you) goes first
void PVE_MODE_NORMAL(int chessLayout[8][8], int playercnt, int comcnt) {
    int quit = 0;
    string sMode = "PVE_NORMAL";
    showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
    while (true) {
        if (!isEnd(chessLayout, P)) {
            string info = player(chessLayout, playercnt, comcnt, quit, 3);
            if (quit) {
                return;
            }
            showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
        }
        else {
            comcnt = 49 - playercnt;
            break;
        }
        cout << "The computer is processing...\n";
        sleep(3);
        if (!isEnd(chessLayout, C)) {
            string info = computer_Normal(chessLayout, playercnt, comcnt);
            showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
        }
        else {
            playercnt = 49 - comcnt;
            break;
        }
        if (playercnt == 0 || comcnt == 0)
            break;
    }
    if (playercnt > comcnt) {
        showVictory();
        cout << "YOU WIN!" << endl;
    }
    else if (playercnt < comcnt) {
        showDefeat();
        cout << "YOU LOSE!" << endl;
    }
    cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
    getchar();
    getchar();
}

// pve hard mode, black (you) goes first
void PVE_MODE_HARD(int chessLayout[8][8], int playercnt, int comcnt) {
    int quit = 0;
    string sMode = "PVE_HARD";
    showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
    while (true) {
        if (!isEnd(chessLayout, P)) {
            string info = player(chessLayout, playercnt, comcnt, quit, 4);
            if (quit) {
                return;
            }
            showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
        }
        else {
            comcnt = 49 - playercnt;
            break;
        }
        cout << "The computer is processing...\n";
        sleep(3);
        if (!isEnd(chessLayout, C)) {
            string info = computer_Hard(chessLayout, playercnt, comcnt);
            showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
        }
        else {
            playercnt = 49 - comcnt;
            break;
        }
        if (playercnt == 0 || comcnt == 0)
            break;
    }
    if (playercnt > comcnt) {
        showVictory();
        cout << "YOU WIN!" << endl;
    }
    else if (playercnt < comcnt) {
        showDefeat();
        cout << "YOU LOSE!" << endl;
    }
    cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
    getchar();
    getchar();
}

void PVE_MODE_DEVIL(int chessLayout[8][8], int playercnt, int comcnt) {
    int quit = 0;
    string sMode = "PVE_DEVIL";
    showBoard(chessLayout, playercnt, comcnt, sMode, E, "NULL");
    while (true) {
        if (!isEnd(chessLayout, P)) {
            string info = player(chessLayout, playercnt, comcnt, quit, 5);
            if (quit) {
                return;
            }
            showBoard(chessLayout, playercnt, comcnt, sMode, P, info);
        }
        else {
            comcnt = 49 - playercnt;
            break;
        }
        cout << "The computer is processing...\n";
        sleep(1);
        if (!isEnd(chessLayout, C)) {
            string info = computer_Devil(chessLayout, playercnt, comcnt);
            showBoard(chessLayout, playercnt, comcnt, sMode, C, info);
        }
        else {
            playercnt = 49 - comcnt;
            break;
        }
        if (playercnt == 0 || comcnt == 0)
            break;
    }
    if (playercnt > comcnt) {
        showVictory();
        cout << "YOU WIN!" << endl;
    }
    else if (playercnt < comcnt) {
        showDefeat();
        cout << "YOU LOSE!" << endl;
    }
    cout << "PRESS ANY BUTTON TO CONTINUE..." << endl;
    getchar();
    getchar();
}



// save the record
void saveRecordFile(int chessLayout[8][8], int playercnt, int comcnt, int mode, int sequence) {
    ofstream outfile;
    outfile.open("/Users/kuangyuxuan/CLionProjects/Ataxx/cmake-build-debug/recordFile.txt", ios::in);
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            outfile << chessLayout[i][j] << endl;
        }
    }
    outfile << playercnt << endl;
    outfile << comcnt << endl;
    outfile << mode << endl;
    outfile << sequence;
}

// load the record
void loadRecordFile(int chessLayout[8][8], int& playercnt, int& comcnt, int& mode, int& sequence) {
    ifstream infile;
    infile.open("/Users/kuangyuxuan/CLionProjects/Ataxx/cmake-build-debug/recordFile.txt", ios::out);
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            infile >> chessLayout[i][j];
        }
    }
    infile >> playercnt >> comcnt >> mode >> sequence;
}

// show rules of the game ataxx
void showRules() {
    system("clear");
    printf("#####################################################################\n");
    printf("##                              RULES:                             ##\n");
    printf("##   THE initial arrangement is that both sides place two pieces   ##\n"
           "##   on the outermost diagonal square.                             ##\n");
    printf("##   PLAYERS must take turns to move one piece to an empty chess   ##\n"
           "##   position, which can be one of the adjacent eight squares      ##\n"
           "##   (including diagonally adjacent squares), or one of the next   ##\n"
           "##   eight squares separated by one square. The moved new position ##\n"
           "##   will make all opponents in the neighboring eight squares      ##\n"
           "##   become your own. If the piece is moved to the adjacent eight  ##\n"
           "##   squares, a new one will appear in the original position.      ##\n");
    printf("##   IF you can't play chess, you must abstain. When both sides    ##\n"
           "##   can't play, the game ends. The one with the most pieces wins. ##\n");
    printf("##                                                                 ##\n");
    printf("#####################################################################\n");
    cout << endl;
    cout << "PRESS ANY BUTTON TO CONTINUE...";
    getchar();
    getchar();
}

// view more information about the developer
void aboutMe() {
    system("clear");
    printf("############################################################\n");
    printf("##                                                        ##\n");
    printf("##                    More Information:                   ##\n");
    printf("##           https://github.com/yxKryptonite/Ataxx        ##\n");
    printf("##           https://gitee.com/yxKryptonite/ataxx         ##\n");
    printf("##                                                        ##\n");
    printf("############################################################\n");
    cout << endl;
    cout << "PRESS ANY BUTTON TO CONTINUE...";
    getchar();
    getchar();
}


// show the winning menu
void showVictory() {
    printf("                                                                                                               ,---. \n");
    printf(" ,-----.                                       ,--.          ,--.          ,--.  ,--.                          |   | \n");
    printf("'  .--./ ,---. ,--,--,  ,---. ,--.--. ,--,--.,-'  '-.,--.,--.|  | ,--,--.,-'  '-.`--' ,---. ,--,--,  ,---.     |  .' \n");
    printf("|  |    | .-. ||     | | .-. ||  .--'' ,-.  |'-.  .-'|  ||  ||  |' ,-.  |'-.  .-',--.| .-. ||     | (  .-'     |  |  \n");
    printf("'  '--'\\| '-' '|  ||  |' '-' '|  |   | '-'  |  |  |  '  ''  '|  || '-'  |  |  |  |  |' '-' '|  ||  |.-'  `)    `--'  \n");
    printf(" `-----' `---' `--''--'.`-  / `--'    `--`--'  `--'   `----' `--' `--`--'  `--'  `--' `---' `--''--'`----'     .--.  \n");
    printf("                       `---'                                                             ,---.                 '--'  \n");
    printf("                            ,--.   ,--.,-----. ,--. ,--.    ,--.   ,--.,--.,--.  ,--.    |   |                       \n");
    printf("                             \\  `.'  /'  .-.  '|  | |  |    |  |   |  ||  ||  ,'.|  |    |  .'                       \n");
    printf("                              '.    / |  | |  ||  | |  |    |  |.'.|  ||  ||  |' '  |    |  |                        \n");
    printf("                                |  |  '  '-'  ''  '-'  '    |   ,'.   ||  ||  | `   |    `--'                        \n");
    printf("                                `--'   `-----'  `-----'     '--'   '--'`--'`--'  `--'    .--.                        \n");
    printf("                                                                                         '--'                        \n");
    sleep(5);
    system("clear");
}

// show the losing menu
void showDefeat() {
    printf("                                                                                             ,---. \n");
    printf("     ,--.,--. ,--. ,---. ,--------.    ,--.    ,-----.  ,---.  ,------.    ,--.,--------.    |   | \n");
    printf("     |  ||  | |  |'   .-''--.  .--'    |  |   '  .-.  ''   .-' |  .---'    |  |'--.  .--'    |  .' \n");
    printf(",--. |  ||  | |  |`.  `-.   |  |       |  |   |  | |  |`.  `-. |  `--,     |  |   |  |       |  |  \n");
    printf("|  '-'  /'  '-'  '.-'    |  |  |       |  '--.'  '-'  '.-'    ||  `---.    |  |   |  |       `--'  \n");
    printf(" `-----'  `-----' `-----'   `--'       `-----' `-----' `-----' `------'    `--'   `--'       .--.  \n");
    printf("                                                                                             '--'  \n");
    sleep(5);
    system("clear");
}



// show black wins
void showBlackWin() {
    printf("  ____  _               _____ _  __ __          _______ _   _  _____   _ \n");
    printf(" |  _ \\| |        /\\   / ____| |/ / \\ \\        / /_   _| \\ | |/ ____| | |\n");
    printf(" | |_) | |       /  \\ | |    | ' /   \\ \\  /\\  / /  | | |  \\| | (___   | |\n");
    printf(" |  _ <| |      / /\\ \\| |    |  <     \\ \\/  \\/ /   | | | . ` |\\___ \\  | |\n");
    printf(" | |_) | |____ / ____ \\ |____| . \\     \\  /\\  /   _| |_| |\\  |____) | |_|\n");
    printf(" |____/|______/_/    \\_\\_____|_|\\_\\     \\/  \\/   |_____|_| \\_|_____/  (_)\n");
    printf("                                                                         \n");
    sleep(5);
    system("clear");
}

// show white wins
void showWhiteWin() {
    printf(" __          ___    _ _____ _______ ______  __          _______ _   _  _____   _ \n");
    printf(" \\ \\        / / |  | |_   _|__   __|  ____| \\ \\        / /_   _| \\ | |/ ____| | |\n");
    printf("  \\ \\  /\\  / /| |__| | | |    | |  | |__     \\ \\  /\\  / /  | | |  \\| | (___   | |\n");
    printf("   \\ \\/  \\/ / |  __  | | |    | |  |  __|     \\ \\/  \\/ /   | | | . ` |\\___ \\  | |\n");
    printf("    \\  /\\  /  | |  | |_| |_   | |  | |____     \\  /\\  /   _| |_| |\\  |____) | |_|\n");
    printf("     \\/  \\/   |_|  |_|_____|  |_|  |______|     \\/  \\/   |_____|_| \\_|_____/  (_)\n");
    printf("                                                                                 \n");
    sleep(5);
    system("clear");
}

// judge whether your to-move chessman can move to another place
bool canMove(int chessLayout[8][8], int ox, int oy) {
    for (int i = ox - 2; i <= ox + 2; ++i) {
        for (int j = oy - 2; j <= oy + 2; ++j) {
            if (isLegal(chessLayout, i, j, ox, oy)) {
                return true;
            }
        }
    }
    return false;
}

// count the maximum area of rectangles in the array
int count_matrix(int chessLayout[8][8], int state) {
    int mine[8][8] = {0};
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == state) {
                mine[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (mine[i][j]) {
                mine[i][j] = mine[i][j-1] + 1;
            }
        }
    }
    int width, len, area;
    int maximum = 0;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (mine[i][j]) {
                width = 1;
                len = mine[i][j];
                area = len * width;
                maximum = max(maximum, area);
                int minLen = mine[i][j];
                for (int k = i-1; k >= 1; --k) {
                    if (mine[k][j] == 0)
                        break;
                    minLen = min(minLen, mine[k][j]);
                    len = min(mine[k][j], mine[i][j]);
                    width++;
                    area = width * minLen;
                    maximum = max(maximum, area);
                }
            }
        }
    }
    return maximum;
}

// the evaluation function
int evaluate(int playercnt, int comcnt) {
    return comcnt - playercnt;
}

void copy(int chessLayout[8][8], int tmpLayout[8][8], int& playercnt, int& comcnt, int& tmpPlayer, int& tmpCom) {
    tmpPlayer = playercnt;
    tmpCom = comcnt;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            tmpLayout[i][j] = chessLayout[i][j];
        }
    }
}

void resume(int chessLayout[8][8], int tmpLayout[8][8], int& playercnt, int& comcnt, int& tmpPlayer, int& tmpCom) {
    playercnt = tmpPlayer;
    comcnt = tmpCom;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            chessLayout[i][j] = tmpLayout[i][j];
        }
    }
}

void minmax(int chessLayout[8][8], int depth, int playercnt, int comcnt) {
    for (int i = 0; i < 10; ++i) {
        best_move[i] = -1;
    }
    int best_val = -50;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] != C)
                continue;
            for (int x = i-2; x <= i+2; ++x) {
                for (int y = j-2; y <= j+2; ++y) {
                    if (isLegal(chessLayout, x, y, i, j)) {
                        int tmpLayoutForMinMax[8][8];
                        int tmpPlayer, tmpCom;
                        copy(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        refreshLayout(chessLayout, x, y, C, i, j, playercnt, comcnt);
                        int val = Min(chessLayout, depth-1, playercnt, comcnt);
                        resume(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        if (val > best_val) {
                            best_val = val;
                            best_move[0] = i;
                            best_move[1] = j;
                            best_move[2] = x;
                            best_move[3] = y;
                        }
                    }
                }
            }
        }
    }
}

int Max(int chessLayout[8][8], int depth, int playercnt, int comcnt) {
    int maximum = -50;
    if (depth <= 0) {
        return evaluate(playercnt, comcnt);
    }
    if (!canMoveForMinMax(chessLayout, C)) {
        if (!canMoveForMinMax(chessLayout, P)) {
            return evaluate(playercnt, comcnt);
        }
        return Min(chessLayout, depth, playercnt, comcnt);
    }
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] != C)
                continue;
            for (int x = i-2; x <= i+2; ++x) {
                for (int y = j-2; y <= j+2; ++y) {
                    if (isLegal(chessLayout, x, y, i, j)) {
                        int tmpLayoutForMinMax[8][8];
                        int tmpPlayer, tmpCom;
                        copy(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        refreshLayout(chessLayout, x, y, C, i, j, playercnt, comcnt);
                        int val = Min(chessLayout, depth-1, playercnt, comcnt);
                        resume(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        maximum = max(maximum, val);
                    }
                }
            }
        }
    }
    return maximum;
}

int Min(int chessLayout[8][8], int depth, int playercnt, int comcnt) {
    int minimum = 50;
    if (depth <= 0) {
        return evaluate(playercnt, comcnt);
    }
    if (!canMoveForMinMax(chessLayout, P)) {
        if (!canMoveForMinMax(chessLayout, C)) {
            return evaluate(playercnt, comcnt);
        }
        return Max(chessLayout, depth, playercnt, comcnt);
    }
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] != P)
                continue;
            for (int x = i-2; x <= i+2; ++x) {
                for (int y = j-2; y <= j+2; ++y) {
                    if (isLegal(chessLayout, x, y, i, j)) {
                        int tmpLayoutForMinMax[8][8];
                        int tmpPlayer, tmpCom;
                        copy(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        refreshLayout(chessLayout, x, y, P, i, j, playercnt, comcnt);
                        int val = Max(chessLayout, depth-1, playercnt, comcnt);
                        resume(chessLayout, tmpLayoutForMinMax, playercnt, comcnt, tmpPlayer, tmpCom);
                        minimum = min(minimum, val);
                    }
                }
            }
        }
    }
    return minimum;
}

bool canMoveForMinMax(int chessLayout[8][8], int state) {
    int cnt = 0;
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            if (chessLayout[i][j] == state) {
                for (int x = i-2; x <= i+2; ++x) {
                    for (int y = j-2; y <= j+2; ++y) {
                        if (isLegal(chessLayout, x, y, i, j)) {
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    if (cnt)
        return true;
    else
        return false;
}



