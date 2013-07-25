#include <sstream>

#include "Game.h"
#include "Player.h"
#include "UserInterface.h"

int main() {
    UserInterface uInter = UserInterface();
    Player *player1 = NULL;
    Player *player2 = NULL;
    std::string winMsgs[] = {"Naught", " Cross "};
    uInter.printScreen(std::vector<char>(9, ' '));

    while (true) {
        int choice = 0;
        choice = uInter.menuLoop();

        if (choice == 0) {
            int i = Game::randInt(2048);
            player1 = new Player('O', ((i % 2) == 0) ? PlayerType::Human : PlayerType::Bot);
            player2 = new Player('X', ((i % 2) != 0) ? PlayerType::Human : PlayerType::Bot);
        } else if (choice == 1) {
            player1 = new Player('O', PlayerType::Human);
            player2 = new Player('X', PlayerType::Human);
        } else if (choice == 2)
            break;

        uInter.clearScreen();
        Game game = Game();
        while (!game.isOver) {
            uInter.printScreen(game.getBoard());
            if (game.checkWin(game.getBoard()) != game.noWin)
                break;
            int move = 0;
            Player curPlayer = (((game.getTurn() % 2) != 0) ? *player1 : *player2);
            if (curPlayer.getType() == PlayerType::Bot)
                move = game.botMove(curPlayer.getPiece());
            else
                move = uInter.getUserMove();

            std::stringstream ss;
            ss << ((curPlayer.getPiece() == 'O') ? "O: " : "X: ") << move;
            uInter.addHistory(game.getTurn(), ss.str());
            if (!game.addMove(curPlayer.getPiece(), move))
                uInter.printMessage("Invalid", "move!");
        }

        int gameResult = game.checkWin(game.getBoard());
        if (gameResult == game.tie)
            uInter.printMessage("Tie   ", "game!");
        else
            uInter.printMessage(winMsgs[gameResult], "wins!");
    }

    delete player1;
    delete player2;
    return 0;
}
