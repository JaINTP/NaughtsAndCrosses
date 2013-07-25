#include "ConsoleHandler.h"

/* Constructor.
 *
 * Instantiates member variables.
 */
ConsoleHandler::ConsoleHandler(void) {
    out = GetStdHandle(STD_OUTPUT_HANDLE);
}

/* Clears the console screen. */
void ConsoleHandler::clearScreen() {
    DWORD written;
    COORD coord = {0, 0};
    FillConsoleOutputCharacter(out, ' ', 80*25, coord, &written);
    SetConsoleCursorPosition(out, coord);
}

/* Getter.
 *
 * Returns a COORD for the cursor position.
 */
COORD ConsoleHandler::getCursorPos() {
    CONSOLE_SCREEN_BUFFER_INFO si;
    GetConsoleScreenBufferInfo(out, &si);
    return si.dwCursorPosition;
}

/* Getter.
 *
 * Returns the width of the console.
 */
int ConsoleHandler::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO si;
    GetConsoleScreenBufferInfo(out, &si);
    COORD coord = si.dwSize;
    return coord.X;
}

/* Getter.
 *
 * Returns the height of the console.
 */
int ConsoleHandler::getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO si;
    GetConsoleScreenBufferInfo(out, &si);
    COORD coord = si.dwSize;
    return coord.Y;
}

/* Toggles whether the console cursor is visible. */
void ConsoleHandler::toggleConsoleCursor() {
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(this->out, &ci);
    ci.bVisible = (ci.bVisible == TRUE) ? FALSE : TRUE;
    SetConsoleCursorInfo(out, &ci);
}

/* Sets the console title.
 *
 * Parameters:
 * string: A C stlye string to be used as the console title.
 */
void ConsoleHandler::setTitle(char* string) {
    SetConsoleTitleA(string);
}

/* Sets the console title.
 *
 * Parameters:
 * string: A string to be used as the console title.
 */
void ConsoleHandler::setTitle(std::string string) {
    SetConsoleTitleA(string.c_str());
}

/* Sets the position of the console cursor.
 *
 * Parameters:
 * coord: A COORD structure to move the cursor to.
 */
void ConsoleHandler::setCursorPos(COORD coord) {
    SetConsoleCursorPosition(out, coord);
}

/* Sets the position of the console cursor.
 *
 * Parameters:
 * x: An integer representing the place on the x axis to move the cursor to.
 * y: An integer representing the place on the y axis to move the cursor to.
 */
void ConsoleHandler::setCursorPos(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(out, coord);
}

/* Prints a string on a given row.
 *
 * Parameters:
 * row: An integer representing the row in the console for the string to be printed on.
 * line: The C style string to be printed.
 */
void ConsoleHandler::printLine(int row, char* line) {
    printLine(row, 0, line);
}

/* Prints a string on a given row.
 *
 * Parameters:
 * row: An integer representing the row in the console for the string to be printed on.
 * line: The string to be printed.
 */
void ConsoleHandler::printLine(int row, std::string line) {
    printLine(row, 0, line);
}

/* Prints a string at a given position.
 *
 * Parameters:
 * row: An integer representing the row in the console for the string to be printed on.
 * col: An integer representing the column in which ti start printing.
 * line: The C style string to be printed.
 */
void ConsoleHandler::printLine(int row, int col, char* line) {
    setCursorPos(row, col);
    std::cout << line << std::endl;
}

/* Prints a string at a given position.
 *
 * Parameters:
 * row: An integer representing the row in the console for the string to be printed on.
 * col: An integer representing the column in which ti start printing.
 * line: The string to be printed.
 */
void ConsoleHandler::printLine(int row, int col, std::string line) {
    setCursorPos(row, col);
    std::cout << line << std::endl;
}

/* Allows for the setting of console text attributes such as foreground and background
 * colours.
 *
 * Parameters:
 * attributes: The character attributes.
 */
void ConsoleHandler::setConsoleTextAttribute(WORD attributes) {
    SetConsoleTextAttribute(out, attributes);
}
