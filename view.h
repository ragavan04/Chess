#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Board;
class View{
    public:
        virtual void notify(const Board &board, int srcRow, int srcCol, int destRow, int destCol) = 0;
        virtual ~View() {}; // virtual dtor
    
};

#endif