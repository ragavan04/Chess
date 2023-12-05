#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include "leveltwo.h"
#include <utility>
#include <set>
#include <random>
using namespace std;

class LevelThree : public LevelTwo {
    vector<std::pair<Position, Position>> moveHistory;
public:
    LevelThree(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMove(const pair<Position, Position> &move, Board* board) const;
    bool avoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const;
    int getComputerLevel() const override { return 4; }
};

#endif
