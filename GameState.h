#ifndef CHESS_GAMESTATE_H
#define CHESS_GAMESTATE_H

#include <vector>
#include <string>

class GameState {
    private:
        std::vector<std::vector<std::string>> board;
    public:
        GameState();
        std::vector<std::vector<std::string>> GetGameState();
        void ChangeSquare(int rank, int file, std::string new_state);
};


#endif //CHESS_GAMESTATE_H
