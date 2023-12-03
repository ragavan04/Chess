#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

using namespace std;

class Computer : public Player{
    public:
    Computer(const string& colour, string playerType) : Player(colour, playerType) {}
    virtual pair<Position, Position> algorithm() const = 0;
};

#endif
