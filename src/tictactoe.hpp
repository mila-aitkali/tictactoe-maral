#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <array>
#include <string>

void initializeBoard(std::array<char, 9>& board);
void printBoard(const std::array<char, 9>& board);
bool isDigitsOnly(const std::string& input);
bool isValidMove(const std::array<char, 9>& board, const std::string& input, int& move);
bool checkWin(const std::array<char, 9>& board, char player);
bool checkDraw(const std::array<char, 9>& board);
bool playAgainPrompt();
int chooseGameMode();
int computerMove(const std::array<char, 9>& board);
void playGame(int mode);

#endif