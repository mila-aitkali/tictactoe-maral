#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <array>
#include <string>

class TicTacToe {
public:
    TicTacToe();

    void initializeBoard();
    void printBoard() const;
    bool isDigitsOnly(const std::string& input) const;
    bool isValidMove(const std::string& input, int& move) const;
    void applyMove(int move, char player);
    bool checkWin(char player) const;
    bool checkDraw() const;
    int computerMove() const;
    char getCurrentPlayer() const;
    void switchPlayer();

private:
    std::array<char, 9> board;
    char currentPlayer;
};

#endif