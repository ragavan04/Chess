#include "board.h"
#include "textdisplay.h"
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
using namespace std;

Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false}, views{vector<View*>(2, nullptr)} {
    views[0] = new TextDisplay();
}

void Board::standardBoardSetup(){
    // Setting up pawns
    for (int i = 0; i < 8; ++i) {
        grid[1][i] = new Pawn(Piece::PAWN, "white", {1, i}, *this); // White pawns
        grid[6][i] = new Pawn(Piece::PAWN, "black", {6, i}, *this); // Black pawns
    }

    // Setting up rooks
    grid[0][0] = new Rook(Piece::ROOK, "white", {0, 0}, *this);
    grid[0][7] = new Rook(Piece::ROOK, "white", {0, 7}, *this);
    grid[7][0] = new Rook(Piece::ROOK, "black", {7, 0}, *this);
    grid[7][7] = new Rook(Piece::ROOK, "black", {7, 7}, *this);

    // Setting up knights
    grid[0][1] = new Knight(Piece::KNIGHT, "white", {0, 1}, *this);
    grid[0][6] = new Knight(Piece::KNIGHT, "white", {0, 6}, *this);
    grid[7][1] = new Knight(Piece::KNIGHT, "black", {7, 1}, *this);
    grid[7][6] = new Knight(Piece::KNIGHT, "black", {7, 6}, *this);

    // Setting up bishops
    grid[0][2] = new Bishop(Piece::BISHOP, "white", {0, 2}, *this);
    grid[0][5] = new Bishop(Piece::BISHOP, "white", {0, 5}, *this);
    grid[7][2] = new Bishop(Piece::BISHOP, "black", {7, 2}, *this);
    grid[7][5] = new Bishop(Piece::BISHOP, "black", {7, 5}, *this);

    // Setting up queens
    grid[0][3] = new Queen(Piece::QUEEN, "white", {0, 3}, *this);
    grid[7][3] = new Queen(Piece::QUEEN, "black", {7, 3}, *this);

    // Setting up kings
    grid[0][4] = new King(Piece::KING, "white", {0, 4}, *this);
    grid[7][4] = new King(Piece::KING, "black", {7, 4}, *this);
}


void Board::makeMove(Piece *p, Position newPos){
    if (p->isValid(newPos)) {
        // Clear the piece's previous position on the board
        grid[p->getX()][p->getY()] = nullptr;

        // Capture handling if there is a piece at newPos
        if (grid[newPos.posX][newPos.posY] != nullptr) {
            delete grid[newPos.posX][newPos.posY]; 
        }

        // Move the piece to the new position
        grid[newPos.posX][newPos.posY] = p;
        
        // Update the piece's internal position
        p->setPosition(newPos);
    }
}



void Board::addPiece(char type, Position pos) {

    Piece *p;

   switch(type) {
        case 'p' : 
            p = new Pawn(Piece::PAWN, "white", pos, *this);
            break;
        case 'n' :
            p = new Knight(Piece::KNIGHT, "white", pos, *this); 
            break;
        case 'b' : 
            p = new Bishop(Piece::BISHOP, "white", pos, *this);     
            break;
        case 'r' : 
            p = new Rook(Piece::ROOK, "white", pos, *this); 
            break;
        case 'q' :
            p = new Queen(Piece::QUEEN, "white", pos, *this); 
            break;
        case 'k' :  
            p = new King(Piece::KING, "white", pos, *this); 
            break;
        case 'P' : 
            p = new Pawn(Piece::PAWN, "black", pos, *this); 
            break;
        case 'N' : 
            p = new Knight(Piece::KNIGHT, "black", pos, *this);  
            break;
        case 'B' : 
            p = new Bishop(Piece::BISHOP, "black", pos, *this);     
            break;
        case 'R' : 
            p = new Rook(Piece::ROOK, "black", pos, *this); 
            break;
        case 'Q' :
            p = new Queen(Piece::QUEEN, "black", pos, *this); 
            break;
        case 'K' :
            p = new King(Piece::KING, "black", pos, *this); 
            break;
    }
    
    grid[pos.posX][pos.posY] = p;

}
    
void Board::removePiece(Position pos) {

    if(grid[pos.posX][pos.posY] != nullptr) {
        delete grid[pos.posX][pos.posY];
        grid[pos.posX][pos.posY] = nullptr; 
    }

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



void Board::switchTurns() {
	
	if(turn == 0) {
		turn == 1;
	} else if(turn == 1) {
		turn == 0;
	}

}


int Board::getTurn() const {
    return turn;
}

void Board::clearBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
    }
    for (auto view : views) {
        delete view;
    }
    views.clear();
    turn = 0;
    isWin = false;
}
