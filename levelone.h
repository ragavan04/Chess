#ifndef __LEVELONE_H__
#define __LEVELONE_H__
#include "computer.h"

class LevelOne : public Computer {
public:
    pair<Position, Position> algorithm() const override;
};

#endif
