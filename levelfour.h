#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__
#include "computer.h"
#include "levelthree.h"
using namespace std;

class LevelFour : public LevelThree {
public:
    LevelFour(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMove(const pair<Position, Position> &move, Board* board) const;
    bool moveAvoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const;
    int getComputerLevel() const override { return 4; }
};

#endif
