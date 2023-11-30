#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

using namespace std;

class Human : public Player{
    public:
    Human(const string& colour, string playerType);
    void addToAvailableMoves(Piece* piece);


};


#endif

