#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <string>

class ConsoleHandler {
public:
    ConsoleHandler(void);
    void clearScreen();
    COORD getCursorPos();
    int getConsoleWidth();
    int getConsoleHeight();
    void toggleConsoleCursor();
    void setTitle(char* string);
    void setTitle(std::string string);
    void setCursorPos(COORD coord);
    void setCursorPos(int x, int y);
    void printLine(int row, char* line);
    void printLine(int row, std::string line);
    void printLine(int row, int col, char* line);
    void printLine(int row, int col, std::string line);
    void setConsoleTextAttribute(WORD attributes);

private:
    HANDLE out;
    COORD last;
};
