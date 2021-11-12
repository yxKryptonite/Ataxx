//
// Created by kuangyuxuan on 2021/11/11.
//
#include <iostream>
#include <cmath>
using namespace std;
#define E 0 // E refers to empty
#define P 1 // P refers to player
#define C 2 // C refers to computer

// show the starting menu
void showMenu() {
    printf("##################################\n");
    printf("##       Welcome to Ataxx!      ##\n");
    printf("##                              ##\n");
    printf("##   Please make your choice:   ##\n");
    printf("##          1. Start            ##\n");
    printf("##          2. Suspend          ##\n");
    printf("##          3. Resume           ##\n");
    printf("##          4. Save             ##\n");
    printf("##          5. Load             ##\n");
    printf("##          6. Restart          ##\n");
    printf("##          7. Exit             ##\n");
    printf("##                              ##\n");
    printf("##          Have Fun!           ##\n");
    printf("##################################\n");
}

// output a new chessboard (abolished)
void makeEmptyBoard() {
    system("clear");
    printf(" YOU: 0                 ┃                 COM: 0\n");
    printf(" ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("      1     2     3     4     5     6     7  \n");
    printf("   ┏━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓  \n");
    for (int i = 1; i < 7; ++i) {
        printf(" %d ┃     ┃     ┃     ┃     ┃     ┃     ┃     ┃  \n", i);
        printf("   ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫  \n");
    }
    printf(" 7 ┃     ┃     ┃     ┃     ┃     ┃     ┃     ┃  \n");
    printf("   ┗━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┛  \n");
}

// judge the movement (state refers to player or computer, ox refers to original x, oy be the same)
bool isIllegal(int chessLayout[8][8], int x, int y, int state, int ox, int oy) {
    if (x < 1 || x > 7 || y < 1 || y > 7)
        return false;
    else if (x == ox && y == oy)
        return false;
    else if (chessLayout[x][y] != E)
        return false;
    int dis_x = abs(x - ox);
    int dis_y = abs(y - oy);
    if (dis_x + dis_y <= 4)
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
        chessLayout[x][y] = state;
        playercnt++;
    }
    else {
        chessLayout[ox][oy] = E;
        chessLayout[x][y] = state;
    }
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (chessLayout[i][j] == enemy && state == P) {
                chessLayout[i][j] = state;
                playercnt++;
                comcnt--;
            }
            else if (chessLayout[i][j] == enemy && state == C) {
                chessLayout[i][j] = state;
                comcnt++;
                playercnt--;
            }
        }
    }
}

// the player makes action (from to-move chessman to goal position)
void player(int chessLayout[8][8], int& playercnt, int& comcnt) {
    int x, y, ox, oy;
    printf("Please input the coordinates of your to-move chessman\n");
    printf("X axis: ");
    cin >> ox;
    printf("Y axis: ");
    cin >> oy;
    while (chessLayout[ox][oy] != P) {
        printf("ILLEGAL!!! Please input the coordinates of your to-move chessman again\n");
        printf("X axis: ");
        cin >> ox;
        printf("Y axis: ");
        cin >> oy;
    }
    printf("Please input the coordinates of your goal position\n");
    printf("X axis: ");
    cin >> x;
    printf("Y axis: ");
    cin >> y;
    while (!isIllegal(chessLayout, x, y, P, ox, oy)) {
        printf("ILLEGAL!!! Please move your chess again\n");
        printf("Your x axis: ");
        cin >> x;
        printf("Your y axis: ");
        cin >> y;
    }
    refreshLayout(chessLayout, x, y, P, ox, oy, playercnt, comcnt);
}

// the computer makes action automatically (with algorithm)
void computer(int chessLayout[8][8], int& playercnt, int& comcnt) {

}

// show the chessboard according to the array "chessLayout"
void showBoard(int chessLayout[8][8], int playercnt, int comcnt) {
    system("clear");
    printf(" YOU: %d                 ┃                 COM: %d\n", playercnt, comcnt);
    printf(" ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("      1     2     3     4     5     6     7  \n");
    printf("   ┏━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓  \n");
    printf(" 1 ┃");
    for (int i = 1; i <= 7; ++i) {
        if (chessLayout[1][i] == 1) {
            printf("  ●  ┃");
        }
        else if (chessLayout[1][i] == 2) {
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
}

// initialize the array "chessLayout"
void __init__(int chessLayout[8][8]) {
    chessLayout[1][1] = P;
    chessLayout[7][7] = P;
    chessLayout[1][7] = C;
    chessLayout[7][1] = C;
}


