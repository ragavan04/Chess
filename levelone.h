#ifndef __LEVELONE_H__
#define __LEVELONE_H__
#include "computer.h"

class LevelOne : public Computer {
public:
    LevelOne(const string& colour, string playerType) : Computer(colour, playerType){}
    pair<Position, Position> algorithm() const override;
    int getComputerLevel() const override { return 1; }
};

#endif
