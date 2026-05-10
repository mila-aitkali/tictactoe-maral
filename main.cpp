#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "src/tictactoe.hpp"
using namespace std;

// Returns 1 = Human vs Human, 2 = Human vs Computer, 3 = Computer vs Human
int chooseGameMode() {
    string input;
    while (true) {
        cout << "What kind of game would you like to play?\n";
        cout << "  1. Human vs. Human\n";
        cout << "  2. Human vs. Computer\n";
        cout << "  3. Computer vs. Human\n";
        cout << "What is your selection? ";
        getline(cin, input);
        if (input == "1") {
            return 1;
        } else if (input == "2") {
            return 2;
        } else if (input == "3") {
            return 3;
        } else {
            cout << "\nThat is not a valid selection! Try again.\n\n";
        }
    }
}

bool chooseTrap() {
    string input;
    while (true) {
        cout << "\nWould you like to include a trap cell in your game?\n\n";
        cout << "1. Yes\n";
        cout << "2. No\n\n";
        cout << "What is your selection? ";
        getline(cin, input);
        if (input == "1") return true;
        if (input == "2") return false;
        cout << "\nThat is not a valid selection! Try again.\n";
    }
}

bool playAgainPrompt() {
    string input;
    while (true) {
        cout << "Would you like to play again (yes/no)? ";
        getline(cin, input);
        if (input == "yes") {
            return true;
        }
        if (input == "no") {
            return false;
        }
        cout << "\nThat is not a valid entry!\n\n";
    }
}

void playGame(int mode, bool wantTrap) {
    TicTacToe game;

    // mode 1: Human vs Human    -> X = human,    O = human
    // mode 2: Human vs Computer -> X = human,    O = computer
    // mode 3: Computer vs Human -> X = computer, O = human

    if (wantTrap) {
        game.enableTrap();
        cout << "\nGreat! A trap has been hidden on the board.\n";
    }

    if (mode == 2) {
        cout << "\nGreat! The computer will go second.\n";
    } else if (mode == 3) {
        cout << "\nGreat! The computer will go first.\n";
    }

    game.printBoard();

    while (true) {
        char current = game.getCurrentPlayer();

        bool isComputerTurn =
            (mode == 2 && current == 'O') ||
            (mode == 3 && current == 'X');

        int move = 0;

        if (isComputerTurn) {
            move = game.computerMove();
            cout << "Computer plays in spot " << move << ".\n";
        } else {
            string input;
            while (true) {
                cout << "What is your move? ";
                getline(cin, input);
                if (game.isValidMove(input, move)) {
                    break;
                }
                cout << "\nThat is not a valid move! Try again.\n";
            }
        }

        if (game.isTrap(move)) {
            cout << "\nOh no! You set off the trap! " << current << " loses their turn.\n";
            game.printBoard();
            game.switchPlayer();
            continue;
        }

        game.applyMove(move, current);
        game.printBoard();

        if (game.checkWin(current)) {
            if (isComputerTurn) {
                cout << "Computer wins!\n\n";
            } else {
                cout << "Player " << current << " wins!\n\n";
            }
            break;
        }

        if (game.checkDraw()) {
            cout << "It's a draw...\n\n";
            break;
        }

        game.switchPlayer();
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    cout << "Welcome to Tic-Tac-Toe!\n";
    do {
        int mode = chooseGameMode();
        bool wantTrap = chooseTrap();
        playGame(mode, wantTrap);
    } while (playAgainPrompt());
    cout << "\nGoodbye!\n";
    return 0;
}