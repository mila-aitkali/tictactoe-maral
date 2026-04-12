#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../src/tictactoe.hpp"
using namespace std;

TEST_CASE("Board initializes with all cells available") {
    TicTacToe game;
    int move = 0;
    REQUIRE(game.isValidMove("1", move)); REQUIRE(move == 1);
    REQUIRE(game.isValidMove("2", move)); REQUIRE(move == 2);
    REQUIRE(game.isValidMove("3", move)); REQUIRE(move == 3);
    REQUIRE(game.isValidMove("4", move)); REQUIRE(move == 4);
    REQUIRE(game.isValidMove("5", move)); REQUIRE(move == 5);
    REQUIRE(game.isValidMove("6", move)); REQUIRE(move == 6);
    REQUIRE(game.isValidMove("7", move)); REQUIRE(move == 7);
    REQUIRE(game.isValidMove("8", move)); REQUIRE(move == 8);
    REQUIRE(game.isValidMove("9", move)); REQUIRE(move == 9);
}

TEST_CASE("Valid move is accepted") {
    TicTacToe game;
    int move = 0;
    REQUIRE(game.isValidMove("5", move));
    REQUIRE(move == 5);
}

TEST_CASE("Taken cell is rejected") {
    TicTacToe game;
    game.applyMove(5, 'X');
    int move = 0;
    REQUIRE_FALSE(game.isValidMove("5", move));
}

TEST_CASE("Non-digit input is rejected") {
    TicTacToe game;
    int move = 0;
    REQUIRE_FALSE(game.isValidMove("$", move));
    REQUIRE_FALSE(game.isValidMove("abc", move));
    REQUIRE_FALSE(game.isValidMove("", move));
}

TEST_CASE("Multi-digit input is rejected") {
    TicTacToe game;
    int move = 0;
    REQUIRE_FALSE(game.isValidMove("12", move));
    REQUIRE_FALSE(game.isValidMove("258", move));
}

TEST_CASE("Decimal input is rejected") {
    TicTacToe game;
    int move = 0;
    REQUIRE_FALSE(game.isValidMove("3.5", move));
}

TEST_CASE("Out of range input is rejected") {
    TicTacToe game;
    int move = 0;
    REQUIRE_FALSE(game.isValidMove("0", move));
    REQUIRE_FALSE(game.isValidMove("10", move));
}

TEST_CASE("Win is detected across a row") {
    TicTacToe game;
    game.applyMove(1, 'X');
    game.applyMove(2, 'X');
    game.applyMove(3, 'X');
    REQUIRE(game.checkWin('X'));
}

TEST_CASE("Win is detected across a column") {
    TicTacToe game;
    game.applyMove(1, 'O');
    game.applyMove(4, 'O');
    game.applyMove(7, 'O');
    REQUIRE(game.checkWin('O'));
}

TEST_CASE("Win is detected across a diagonal") {
    TicTacToe game;
    game.applyMove(1, 'X');
    game.applyMove(5, 'X');
    game.applyMove(9, 'X');
    REQUIRE(game.checkWin('X'));
}

TEST_CASE("Draw is detected") {
    TicTacToe game;
    // X O X
    // X O O
    // O X X
    game.applyMove(1, 'X'); game.applyMove(2, 'O'); game.applyMove(3, 'X');
    game.applyMove(4, 'X'); game.applyMove(5, 'O'); game.applyMove(6, 'O');
    game.applyMove(7, 'O'); game.applyMove(8, 'X'); game.applyMove(9, 'X');
    REQUIRE(game.checkDraw());
}

TEST_CASE("Non-draw board is not detected as draw") {
    TicTacToe game;
    game.applyMove(1, 'X'); game.applyMove(2, 'O'); game.applyMove(3, 'X');
    game.applyMove(5, 'O'); game.applyMove(6, 'O');
    game.applyMove(7, 'O'); game.applyMove(8, 'X'); game.applyMove(9, 'X');
    REQUIRE_FALSE(game.checkDraw());
}

TEST_CASE("Computer picks first available spot") {
    TicTacToe game;
    REQUIRE(game.computerMove() == 1);
}

TEST_CASE("Computer skips taken spots") {
    TicTacToe game;
    game.applyMove(1, 'X');
    game.applyMove(2, 'O');
    REQUIRE(game.computerMove() == 3);
}

TEST_CASE("Player starts as X") {
    TicTacToe game;
    REQUIRE(game.getCurrentPlayer() == 'X');
}

TEST_CASE("Player switches correctly") {
    TicTacToe game;
    game.switchPlayer();
    REQUIRE(game.getCurrentPlayer() == 'O');
    game.switchPlayer();
    REQUIRE(game.getCurrentPlayer() == 'X');
}