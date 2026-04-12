#include "tictactoe.hpp"
#include <iostream>
#include <cctype>
using namespace std;

TicTacToe::TicTacToe() : currentPlayer('X') {
    initializeBoard();
}

void TicTacToe::initializeBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
    currentPlayer = 'X';
}

void TicTacToe::printBoard() const {
    cout << "\n";
    cout << "    " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
    cout << "  -----+-----+-----\n";
    cout << "    " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
    cout << "  -----+-----+-----\n";
    cout << "    " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
    cout << "\n";
}

bool TicTacToe::isDigitsOnly(const string& input) const {
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

bool TicTacToe::isValidMove(const string& input, int& move) const {
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

void TicTacToe::applyMove(int move, char player) {
    board[move - 1] = player;
}

bool TicTacToe::checkWin(char player) const {
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

bool TicTacToe::checkDraw() const {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
}

int TicTacToe::computerMove() const {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return i + 1;
        }
    }
    return -1;
}

char TicTacToe::getCurrentPlayer() const {
    return currentPlayer;
}

void TicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}