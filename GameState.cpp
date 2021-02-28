#include "GameState.h"

GameState::GameState()
{
    board = {{"br", "bn", "bb", "bq", "bk", "bb", "bn", "br"},
             {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"-", "-", "-", "-", "-", "-", "-", "-"},
             {"wr", "wn", "wb", "wq", "wk", "wb", "wn", "wr"},
             {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"}};
}

std::vector<std::vector<std::string>> GameState::GetGameState() {
    return board;
}
