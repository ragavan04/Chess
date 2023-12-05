#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include "computer.h"
#include "leveltwo.h"
using namespace std;

class LevelThree : public LevelTwo {
public:
    LevelThree(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMoveThree(const pair<Position, Position> &move, Board* board) const;
    bool moveAvoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const;
    int getComputerLevel() const override { return 3; }
};

#endif
