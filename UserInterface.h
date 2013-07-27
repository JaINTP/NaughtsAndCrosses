#pragma once

#include <string>
#include <vector>
#include <conio.h>
#include "ConsoleHandler.h"

class UserInterface
{
public:
    UserInterface();
    int menuLoop();
    int getUserMove();
    void printDebug(COORD curPos);
    void clearScreen();
    int getSelection(COORD curPos);
    void addHistory(int turn, std::string message);
    void printBoard(const std::vector<char> &board);
    void printScreen(const std::vector<char> &board);
    void printMessage(std::string lineOne, std::string lineTwo);

private:
    ConsoleHandler cHandler;
};
