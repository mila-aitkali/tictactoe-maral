#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"


using namespace std;

TEST_CASE("Board initializes with numbers 1 through 9") {
    array<char, 9> board;
    initializeBoard(board);

    REQUIRE(board[0] == '1');
    REQUIRE(board[1] == '2');
    REQUIRE(board[2] == '3');
    REQUIRE(board[3] == '4');
    REQUIRE(board[4] == '5');
    REQUIRE(board[5] == '6');
    REQUIRE(board[6] == '7');
    REQUIRE(board[7] == '8');
    REQUIRE(board[8] == '9');
}

TEST_CASE("Valid move is accepted") {
    array<char, 9> board;
    initializeBoard(board);
    int move = 0;

    REQUIRE(isValidMove(board, "5", move));
    REQUIRE(move == 5);
}

TEST_CASE("Taken cell is rejected") {
    array<char, 9> board;
    initializeBoard(board);
    board[4] = 'X';
    int move = 0;

    REQUIRE_FALSE(isValidMove(board, "5", move));
}

TEST_CASE("Non-digit input is rejected") {
    array<char, 9> board;
    initializeBoard(board);
    int move = 0;

    REQUIRE_FALSE(isValidMove(board, "$", move));
    REQUIRE_FALSE(isValidMove(board, "abc", move));
    REQUIRE_FALSE(isValidMove(board, "", move));
}

TEST_CASE("Multi-digit input is rejected") {
    array<char, 9> board;
    initializeBoard(board);
    int move = 0;

    REQUIRE_FALSE(isValidMove(board, "12", move));
    REQUIRE_FALSE(isValidMove(board, "258", move));
}

TEST_CASE("Decimal input is rejected") {
    array<char, 9> board;
    initializeBoard(board);
    int move = 0;

    REQUIRE_FALSE(isValidMove(board, "3.5", move));
}

TEST_CASE("Out of range input is rejected") {
    array<char, 9> board;
    initializeBoard(board);
    int move = 0;

    REQUIRE_FALSE(isValidMove(board, "0", move));
    REQUIRE_FALSE(isValidMove(board, "10", move));
}

TEST_CASE("Win is detected across a row") {
    array<char, 9> board = {'X', 'X', 'X', '4', '5', '6', '7', '8', '9'};

    REQUIRE(checkWin(board, 'X'));
}

TEST_CASE("Win is detected across a column") {
    array<char, 9> board = {'O', '2', '3', 'O', '5', '6', 'O', '8', '9'};

    REQUIRE(checkWin(board, 'O'));
}

TEST_CASE("Win is detected across a diagonal") {
    array<char, 9> board = {'X', '2', '3', '4', 'X', '6', '7', '8', 'X'};

    REQUIRE(checkWin(board, 'X'));
}

TEST_CASE("Draw is detected") {
    array<char, 9> board = {'X', 'O', 'X', 'X', 'O', 'O', 'O', 'X', 'X'};

    REQUIRE(checkDraw(board));
}

TEST_CASE("Non-draw board is not detected as draw") {
    array<char, 9> board = {'X', 'O', 'X', '4', 'O', 'O', 'O', 'X', 'X'};

    REQUIRE_FALSE(checkDraw(board));
}