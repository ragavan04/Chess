#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class View{
    public:
        virtual void notify(const Board& board) = 0;
        virtual ~View() {}; // virtual dtor
    
};

#endif