#include "board.h"
using namespace std;

// Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false}, views{vector<View*>(2,nullptr)} {}
Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false} {}


ostream& operator<<(ostream& out, const Board& board) {
    int boardSize = 8;
    vector<vector<char>> theDisplay(boardSize, vector<char>(boardSize));
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
    
    for (int row = 7; row >= 0; --row) {
        out << row + 1 << ' '; // Print row number
        for (int col = 0; col < 8; ++col) {
            out << theDisplay[row][col] << ' ';
        }
        out << '\n';
    }
    out << endl;
    out << "  a b c d e f g h\n"; // Print column labels
    return out;
}

vector<vector<Piece*>> Board::getState() const{
    return grid;
}
