#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include "computer.h"
using namespace std;

class LevelThree : public Computer {
    vector<std::pair<Position, Position>> moveHistory;
public:
    LevelThree(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMove(const pair<Position, Position> &move, Board* board) const;
    bool moveAvoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const;
    int getComputerLevel() const override { return 3; }
};

#endif
