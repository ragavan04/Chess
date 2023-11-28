#include "board.h"
#include "textdisplay.h"
using namespace std;

Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false}, views{vector<View*>(2, nullptr)} {
    views[0] = new TextDisplay();
}

void Board::makeMove(Piece *p, Position newPos){
    if (p->isValid(newPos)) {
        // Clear the piece's previous position on the board
        grid[p->getX()][p->getY()] = nullptr;

        // Capture handling if there is a piece at newPos
        if (grid[newPos.posX][newPos.posY] != nullptr) {
            // Handle capture 
        }

        // Move the piece to the new position
        grid[newPos.posX][newPos.posY] = p;
        
        // Update the piece's internal position
        p->setPosition(newPos);
    }
}






void Board::addPiece(char type, Position pos) {

    //Piece *p;

   switch(type) {
        case 'p' : {}
           p = new Pawn(); 
        case 'n' : {}
            
        case 'b' : {}
            
        case 'r' : {}
            
        case 'q' : {}
            
        case 'k' : {} 
            
        case 'P' : {}
            
        case 'N' : {}
            
        case 'B' : {}
            
        case 'R' : {}
            
        case 'Q' : {}
            
        case 'K' : {}
     
    }
    
    

}





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