#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

using namespace std;

class Computer : public Player{
    public:
    virtual pair<Position, Position> algorithm() const = 0;
};

#endif
