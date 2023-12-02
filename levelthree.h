#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include "computer.h"

class LevelThree : public Computer {
public:
    pair<Position, Position> algorithm() const override;
};

#endif