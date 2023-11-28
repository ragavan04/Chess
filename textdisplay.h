#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "view.h"
class Board;
using namespace std;

class TextDisplay : public View {
    const int boardSize = 8;
    vector<vector<char>> theDisplay;
    public:
        TextDisplay();
        void notify(const Board& board) override;
        ~TextDisplay();
        friend ostream& operator<<(ostream& out, const TextDisplay& td);
};

#endif
