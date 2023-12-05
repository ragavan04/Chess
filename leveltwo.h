#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__
#include "computer.h"
#include "levelone.h"
using namespace std;

class LevelTwo : public LevelOne {

public:
    LevelTwo(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMoveTwo(const pair<Position, Position> &move, Board* board) const;
    int getComputerLevel() const override { return 2; }
};

#endif
