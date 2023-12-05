#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "view.h" 
#include "window.h"
using namespace std;

class Board;
class Piece;

class GraphicsDisplay : public View {
    Xwindow &window;
    int gridSize;
    int dimentions;
public:
    GraphicsDisplay(Xwindow &window, int gridSize);
    void notify(const Board &board, int srcRow, int srcCol, int destRow, int destCol);
    ~GraphicsDisplay();
};

#endif

