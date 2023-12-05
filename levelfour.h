#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__
#include "levelthree.h"
#include <utility>
#include <set>
#include <random>
using namespace std;

class LevelFour : public LevelThree {
    vector<std::pair<Position, Position>> moveHistory;
public:
    LevelFour(const string& colour, string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    int evaluateMove(const pair<Position, Position> &move, Board* board) const;
    bool moveAvoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const;
    int getComputerLevel() const override { return 4; }
};

#endif
