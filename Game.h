#pragma once
#include <vector>
#include <algorithm>
#include <time.h>

class Game {
public:
    bool isOver;
    const int tie;
    const int noWin;
    const char cross;
    const char clear;
    const char naught;
    const int crossWin;
    const int naughtWin;

    Game();
    int getTurn();
    int botMove(char piece);
    bool isLegal(int position);
    static int randInt(int length);
    bool addMove(char piece, int move);
    const std::vector<char> &getBoard();
    int checkWin(std::vector<char> board);

private:
    int turn;
    std::vector<char> board;
};
