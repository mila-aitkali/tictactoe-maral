#include "tictactoe.hpp"
#include <iostream>
#include <cctype>
using namespace std;

void initializeBoard(array<char, 9>& board) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

void printBoard(const array<char, 9>& board) {
    cout << "\n";
    cout << "    " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
    cout << "  -----+-----+-----\n";
    cout << "    " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
    cout << "  -----+-----+-----\n";
    cout << "    " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
    cout << "\n";
}

bool isDigitsOnly(const string& input) {
    if (input.empty()) {
        return false;
    }
    for (char ch : input) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

bool isValidMove(const array<char, 9>& board, const string& input, int& move) {
    if (!isDigitsOnly(input)) {
        return false;
    }
    if (input.size() != 1) {
        return false;
    }
    move = input[0] - '0';
    if (move < 1 || move > 9) {
        return false;
    }
    if (board[move - 1] == 'X' || board[move - 1] == 'O') {
        return false;
    }
    return true;
}

bool checkWin(const array<char, 9>& board, char player) {
    return
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player);
}

bool checkDraw(const array<char, 9>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
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

// Computer picks the first available spot on the board
int computerMove(const array<char, 9>& board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return i + 1; // return 1-indexed position
        }
    }
    return -1; // should never reach here during a valid game
}

void playGame(int mode) {
    array<char, 9> board;
    initializeBoard(board);
    char currentPlayer = 'X';

    // mode 1: Human vs Human    -> X = human,    O = human
    // mode 2: Human vs Computer -> X = human,    O = computer
    // mode 3: Computer vs Human -> X = computer, O = human

    if (mode == 2) {
        cout << "Great! The computer will go second.\n";
    } else if (mode == 3) {
        cout << "Great! The computer will go first.\n";
    }

    printBoard(board);

    while (true) {
        bool isComputerTurn =
            (mode == 2 && currentPlayer == 'O') ||
            (mode == 3 && currentPlayer == 'X');

        int move = 0;

        if (isComputerTurn) {
            move = computerMove(board);
            cout << "Computer plays in spot " << move << ".\n";
        } else {
            string input;
            while (true) {
                cout << "What is your move? ";
                getline(cin, input);
                if (isValidMove(board, input, move)) {
                    break;
                }
                cout << "\nThat is not a valid move! Try again.\n";
            }
        }

        board[move - 1] = currentPlayer;
        printBoard(board);

        if (checkWin(board, currentPlayer)) {
            if (isComputerTurn) {
                cout << "Computer wins!\n\n";
            } else {
                cout << "Player " << currentPlayer << " wins!\n\n";
            }
            break;
        }

        if (checkDraw(board)) {
            cout << "It's a draw!\n\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}