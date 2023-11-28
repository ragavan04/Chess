#include "board.h"
#include "textdisplay.h"
using namespace std;

Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false}, views{vector<View*>(2, nullptr)} {
    views[0] = new TextDisplay();
}

vector<vector<Piece*>> Board::getState() const{
    return grid;
}

void Board::notifyObservers() {
    for (auto view : views) {
        if (view) {
            view->notify(*this);
        }
    }
}

void Board::attach(View *o) {
    views.emplace_back(o);
}

ostream& operator<<(ostream& out, const Board& b) {
    TextDisplay* textDisplay = dynamic_cast<TextDisplay*>(b.views[0]);
    if (textDisplay) {
        out << *textDisplay;
    }
    return out;
}