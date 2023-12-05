#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__
#include "computer.h"
#include "board.h"

class LevelFour : public Computer {
public:
    LevelFour(const std::string& colour, std::string playerType);
    std::pair<Position, Position> algorithm(Board* board) const override;
    int getComputerLevel() const override { return 4; }

private:
    int minimax(Board* board, int depth, bool isMaximizingPlayer, int alpha, int beta) const;
    int evaluateBoardState(Board* board) const;
    
};

#endif
