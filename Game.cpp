#include "Game.h"

/* Constructor.
 *
 * Instantiates member variables.
 */
Game::Game() : cross('X'), naught('O'), clear(' '), naughtWin(0), crossWin(1), tie(2), noWin(3) {
    turn = 1;
    isOver = false;
    board = std::vector<char>(9, ' ');
}

/* Getter.
 *
 * Returns the value of turn.
 */
int Game::getTurn() {
    return turn;
}

/* Move choosing algorithm for the AI.
 *
 * Parameters:
 * piece: The game piece for the AI.
 *
 * Returns an integer in range 0-8 representing a place in a vector.
 */
int Game::botMove(char piece) {
    int ret = 0;
    int favoured[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    std::vector<char> tempBoard = board;
    char opponent = (piece == cross) ? naught : cross;

    for (int i = 0; i < 9; i++) {
        if (isLegal(i)) {
            tempBoard[i] = piece;
            if (checkWin(tempBoard) == ((piece == naught) ? naughtWin : crossWin))
                return i;
            tempBoard[i] = clear;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (isLegal(i)) {
            tempBoard[i] = opponent;
            if (checkWin(tempBoard) == ((opponent == naught) ? naughtWin : crossWin))
                return i;
            tempBoard[i] = clear;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (isLegal(favoured[i]))
            return favoured[i];
    }
    return ret;
}

/* Checks if a given position on the board is free to be used.
 *
 * Parameters:
 * position: An int representing the place in the vector to check.
 *
 * Returns a whether the specified place in the vector is empty.
 */
bool Game::isLegal(int position) {
    return board[position] == clear;
}

/* Generates a random integer.
 *
 * Parameters:
 * length: The higest value that the random number generator should try for.
 *
 * Returns an integer between 0 and length.
 */
int Game::randInt(int length) {
    srand (static_cast<int>(time(NULL))); // Cast to supress warnings when casting time_t to unsigned int on x64 machines.
    return rand() % length;
}

/* Checks if a given move for a given piece is valid and if so, adds it to
 * the board.
 *
 * Parameters:
 * piece: The players game piece.
 * move: An integer representing the position in a vector.
 *
 * Returns whether adding the move to the board was successful.
 */
bool Game::addMove(char piece, int move) {
    if (isLegal(move)) {
        board[move] = piece;
        turn++;
        return true;
    }
    return false;
}

/* Getter.
 *
 * Returns a read only reference to the game board vector.
 */
const std::vector<char> &Game::getBoard() {
    return board;
}

/* Checks if a given board cotains a winning combination.
 *
 * Parameters:
 * board: The vector to be checked for winning combinations.
 *
 * Returns one of four integer values depending on the result of the check.
 */
int Game::checkWin(std::vector<char> board) {
    int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
        {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; ++i) {
        if (board[wins[i][0]] != clear &&
            board[wins[i][0]] == board[wins[i][1]] &&
            board[wins[i][1]] == board[wins[i][2]])
            return (board[wins[i][0]] == cross ? crossWin : naughtWin);
    }

    if (count(board.begin(), board.end(), clear) == 0)
        return tie;
    return noWin;
}
