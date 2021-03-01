#include "GameState.h"

GameState::GameState()
{
    board = {{"br", "bn", "bb", "bq", "bk", "bb", "bn", "br"},
             {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
             {"wr", "wn", "wb", "wq", "wk", "wb", "wn", "wr"}};
}

std::vector<std::vector<std::string>> GameState::GetGameState()
{
    return board;
}

void GameState::ChangeSquare(int rank, int file, std::string new_state)
{
    board[file][rank] = new_state;
}