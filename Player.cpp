#include "Player.h"

/* Constructor.
 *
 * Insatiantes member variables.
 */
Player::Player(char piece, PlayerType type) : piece(piece), type(type) {}

/* Getter.
 *
 * Returns the value of piece.
 */
char Player::getPiece() {
    return piece;
}

/* Getter.
 *
 * Returns the value of type.
 */
PlayerType Player::getType() {
    return type;
}