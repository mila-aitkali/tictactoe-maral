#include <iostream>
#include "src/tictactoe.hpp"
using namespace std;

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    do {
        int mode = chooseGameMode();
        playGame(mode);
    } while (playAgainPrompt());
    cout << "\nGoodbye!\n";
    return 0;
}