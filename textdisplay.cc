#include "textdisplay.h"
#include "board.h"

TextDisplay::TextDisplay() {
    theDisplay.resize(boardSize, vector<char>(boardSize, ' '));
}

void TextDisplay::notify(const Board& board) {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board.getState()[row][col] != nullptr) {
                //theDisplay[row][col] = board.getState()[row][col]->displayChar(); 
            } else {
                // Set underscore for dark squares and space for light squares
                theDisplay[row][col] = ((row + col) % 2 == 0) ? ' ' : '_';
            }
        }
    }
}

TextDisplay::~TextDisplay() {}

ostream& operator<<(ostream& out, const TextDisplay& td) {
    for (int row = 7; row >= 0; --row) {
        out << row + 1 << ' '; // Print row number
        for (int col = 0; col < 8; ++col) {
            out << td.theDisplay[row][col] << ' ';
        }
        out << '\n';
    }
    out << endl;
    out << "  a b c d e f g h\n"; // Print column labels
    return out;
}
