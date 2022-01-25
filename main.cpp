#include <iostream>
#include <unistd.h>
#include "func.h"
#define E 0 // E refers to empty
#define P 1 // P refers to player
#define C 2 // C refers to computer or opponent player (pvp mode)
using namespace std;

int main() {
    int mode, sequence;
    int ctrl;
    bool flag = false;
    while (true) {
        int playercnt = 2, comcnt = 2;
        int chessLayout[8][8] = {0};
        showMenu();
        cin >> ctrl;
        switch (ctrl) {
            case 1:
                __init__(chessLayout);
                PVP_MODE(chessLayout, playercnt, comcnt, 1);
                break;
            case 2:
                __init__(chessLayout);
                PVE_MODE_EASY(chessLayout, playercnt, comcnt);
                break;
            case 3:
                __init__(chessLayout);
                PVE_MODE_NORMAL(chessLayout, playercnt, comcnt);
                break;
            case 4:
                __init__(chessLayout);
                PVE_MODE_HARD(chessLayout, playercnt, comcnt);
                break;
            case 5:
                loadRecordFile(chessLayout, playercnt, comcnt, mode, sequence);
                if (mode == 1) {
                    PVP_MODE(chessLayout, playercnt, comcnt, sequence);
                }
                else if (mode == 2) {
                    PVE_MODE_EASY(chessLayout, playercnt, comcnt);
                }
                else if (mode == 3) {
                    PVE_MODE_NORMAL(chessLayout, playercnt, comcnt);
                }
                else if (mode == 4) {
                    PVE_MODE_HARD(chessLayout, playercnt, comcnt);
                }
                else if (mode == 5) {
                    PVE_MODE_DEVIL(chessLayout, playercnt, comcnt);
                }
                break;
            case 6:
                showRules();
                break;
            case 7:
                aboutMe();
                break;
            case 8:
                flag = true;
                cout << "GOODBYE!" << endl;
                break;
            case 9:
                __init__(chessLayout);
                PVE_MODE_DEVIL(chessLayout, playercnt, comcnt);
                break;
            default:
                cout << "DEVELOPING..." << endl;
                sleep(2);
                break;
        }
        if (flag)
            break;
    }

    return 0;
}
