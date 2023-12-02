#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__
#include "computer.h"

class LevelTwo : public Computer {
public:
    pair<Position, Position> algorithm() const override;
};

#endif
