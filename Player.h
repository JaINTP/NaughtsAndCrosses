#pragma once

enum PlayerType { Human, Bot };

class Player {
public:
    Player(char piece, PlayerType type);
    char getPiece();
    PlayerType getType();

private:
    char piece;
    PlayerType type;
};
