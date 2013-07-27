#include "UserInterface.h"

const int ENTER = 13;
const int UP = 72;
const int LEFT = 75;
const int RIGHT = 77;
const int DOWN = 80;

/* Constructor.
 *
 * Instantiates member variables.
 */
UserInterface::UserInterface() {
    cHandler = ConsoleHandler();
    cHandler.setTitle("Naughts and Crosses!");

}

/* Handles user input for the main game menu.
 *
 * Returns: An integer representation of the selected menu index.
 */
int UserInterface::menuLoop() {
    char ch;
    COORD curPos = {2, 5};
    while (true) {
        cHandler.setCursorPos(curPos);
        ch = _getch();
        switch (ch) {
        case ENTER:
            return (cHandler.getCursorPos().Y - 5) / 2;
        case UP:
            curPos.Y += (curPos.Y != 5 ? -2 : 4);
            break;
        case DOWN:
            curPos.Y += (curPos.Y != 9 ? 2 : -4);
            break;
        }
    }
}

/* Handles user input for the game board.
 *
 * Returns: An integer representation of the index the user selects.
 */
int UserInterface::getUserMove() {
    char ch;
    COORD curPos = {27, 7};
    while (true) {
        cHandler.setCursorPos(curPos);
        printDebug(curPos);
        ch = _getch();
        switch (ch) {
        case ENTER:
            return getSelection(curPos);
        case UP:
            curPos.Y += (curPos.Y != 5 ? -2 : 4);
            break;
        case LEFT:
            curPos.X += (curPos.X != 23 ? -4 : 8);
            break;
        case RIGHT:
            curPos.X += (curPos.X != 31 ? 4 : -8);
            break;
        case DOWN:
            curPos.Y += (curPos.Y != 9 ? 2 : -4);
            break;
        }
    }
}

/* Prints debug information related to the cursor position. */
void UserInterface::printDebug(COORD curPos) {
    cHandler.setCursorPos(5, 13);
    std::cout << "Debug Info";
    cHandler.setCursorPos(2, 17);
    std::cout << "Cursor Coords";
    cHandler.setCursorPos(2, 18);
    std::cout << ((curPos.X < 10) ? "X:  " : "X: ") << curPos.X << "  ";
    std::cout << ((curPos.Y < 10) ? " Y:  " : " Y: ") << curPos.Y << "  ";
    cHandler.setCursorPos(2, 21);
    std::cout << "Aray Coords";  
    cHandler.setCursorPos(2, 22);
    std::cout << "X: " << (curPos.X - 23) / 4 << " Y: "<< (curPos.Y - 5) / 2 << "  ";
    cHandler.setCursorPos(2, 19);
    std::cout << "VecPos: " << getSelection(curPos) << "  ";
    cHandler.setCursorPos(2, 23);
    std::cout << "RowMul: " << (curPos.Y -2) / 2 << "  ";
    cHandler.setCursorPos(curPos);
}

/* Clears the console. */
void UserInterface::clearScreen() {
    cHandler.clearScreen();
}

/* Calculates the position in an array pointed to by the cursor position.
 *
 * Parameters:
 * curPos: The current cursor position.
 *
 * Algorigthm explanation:
 *
 * ( ( ( y - yp ) / ys ) * cpr ) + ( ( x - xp ) / xs )
 *
 * y: The position of the cursor on the Y access.
 * x: The position of the cursor on the X access.
 * yp: The position on the Y access where the first game piece is placed.
 * xp: The position on the X access where the first game piece is placed.
 * ys: The distance to the next piece on the Y access. (Including the piece itself)
 * xs: The distance to the next piece on the X access. (Including the piece itself)
 * cpr: The amount of items displayed on each row. (X access)
 *
 * Returns the index of the array pointed to by the cursor.
 */
int UserInterface::getSelection(COORD curPos) {
    int sel = (((curPos.Y - 5) / 2)* 3) + ((curPos.X - 23) / 4);
    return (sel <= 8 && sel >= 0) ? sel : -1;
}

/* Adds a record to the game history.
 *
 * Parameters:
 * turn: Integer representation of the current turn.
 * message: The string to be printed.
 */
void UserInterface::addHistory(int turn, std::string message) {
    cHandler.setCursorPos((((turn % 2) != 0) ? 25 : 40), ( 16 + (((turn % 2) == 0) ? turn : turn + 1) / 2 ));
    std::cout << message;
}

/* Programatically prints the game board.
 *
 * Parameters:
 * board: A read-only reference to a vector.
 */
void UserInterface::printBoard(const std::vector<char> &board) {
    int row = 0;
    for (int i = 0; i < 5; i++) {
        cHandler.setCursorPos(23, 5 + i);
        if ((i % 2) != 0)
            std::cout << "---------";
        else {
            std::cout << board[row] << " | " << board[row + 1] << " | " << board[row + 2];
            row += 3;
        }
    }
}

/* Prints all the UI elements to the console.
 *
 * Parameters:
 * board: A read-only reference to a vector.
 */
void UserInterface::printScreen(const std::vector<char> &board) {
    COORD curPos = cHandler.getCursorPos();
    /****** Separators ******/
    cHandler.setCursorPos(0, 3);
    for (int i = 0; i < 50; i++)
        std::cout << "-";
    cHandler.setCursorPos(0, 11);
    for (int i = 0; i < 50; i++)
        std::cout << "=";
    cHandler.setCursorPos(0, 15);
    for (int i = 0; i < 50; i++)
        std::cout << "-";
    for (int i = 0; i < 25; i++) {
        cHandler.setCursorPos(20, i);
        std::cout << '|';
        cHandler.setCursorPos(50, i);
        std::cout << '|';
    }
    for ( int i = 4; i < 11; i++) {
        cHandler.setCursorPos(35, i);
        std::cout << '|';
    }
    for (int i = 12; i < 25; i++) {
        cHandler.setCursorPos(35, i);
        std::cout << '|';
    }
    /************************/
    /********* Menu *********/
    cHandler.setCursorPos(8, 1);
    std::cout << "Menu";
    cHandler.setCursorPos(1, 5);
    std::cout << "[ ] Single Player";
    cHandler.setCursorPos(1, 7);
    std::cout << "[ ] Two Player";
    cHandler.setCursorPos(1, 9);
    std::cout << "[ ] Exit";
    /************************/
    /******** Board *********/
    cHandler.setCursorPos(23, 1);
    std::cout << "Player 1: O - Player 2: X";
    cHandler.setCursorPos(27, 4);
    std::cout << "X";
    cHandler.setCursorPos(33, 7);
    std::cout << "Y";
    printBoard(board);
    /************************/
    /******** Moves *********/
    cHandler.setCursorPos(24, 13);
    std::cout << "Player 1";
    cHandler.setCursorPos(39, 13);
    std::cout << "Player 2";
    /************************/
    /******** Debug *********/
    printDebug(curPos);
    /************************/
}

/*.Prints an in game message.
 *
 * Parameters:
 * lineOne: The first line to be printed.
 * lineTwo: The second line to be printed.
 */
void UserInterface::printMessage(std::string lineOne, std::string lineTwo) {
    cHandler.setCursorPos(36 + ((14 - lineOne.length()) / 2), 6);
    std::cout << lineOne;
    cHandler.setCursorPos(36 + ((14 - lineTwo.length()) / 2), 8);
    std::cout << lineTwo;
}
