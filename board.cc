#include "board.h"
#include "textdisplay.h"
#include "player.h"
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

void Board::testBoardSetup(){
    for (int i = 0; i < 8; ++i) {
        grid[1][i] = new Pawn(Piece::PAWN, "white", {1, i}, *this); // White pawns
        grid[6][i] = new Pawn(Piece::PAWN, "black", {6, i}, *this); // Black pawns
    }

    // Setting up rooks
    grid[0][0] = new Rook(Piece::ROOK, "white", {0, 0}, *this);
    grid[0][7] = new Rook(Piece::ROOK, "white", {0, 7}, *this);
    grid[7][0] = new Rook(Piece::ROOK, "black", {7, 0}, *this);
    grid[7][7] = new Rook(Piece::ROOK, "black", {7, 7}, *this);

}


void Board::makeMove(Piece *p, Position newPos){
    if (p->isValid(newPos)) {   

        if(grid[p->getX()][p->getY()] != nullptr && grid[p->getX()][p->getY()]->getType() == Piece::KING) {
            
            // Since king has been selected, check if a castle move is possible
            
            King *king = dynamic_cast<King*>(p);

            // check if king has been moved before and the selected position is two spaces to the left of king
            if(!king->getMove() && (newPos.posY == king->getY() - 2)) {            
                
                // check if king is at least at position c
                if((king->getY() > 1) && !king->getMove()) {

                    // iterate through the left side of the king to find a rook, if pieces are found, castle is not possible
                    for(int i = king->getY() - 2; i >= 0; --i) {
                        if(grid[king->getX()][i] != nullptr && grid[king->getX()][i]->getType() == Piece::ROOK) {
                            // if rook has been found, check if it has been moved
                            Rook *rook = dynamic_cast<Rook*>(grid[king->getX()][i]);

                            if(!rook->getMove()) {
                                // if it hasn't been moved and there are no pieces, in the way, castle is valid
                                grid[king->getX()][i] = nullptr;
                                Position newTempPos{newPos.posX,newPos.posY + 1};
                                grid[newTempPos.posX][newTempPos.posY] = rook;
                                rook->setPosition(newTempPos);
                                delete grid[king->getX()][i];
                                rook->setMove();
                            }

                            break;
                        } else if(grid[king->getX()][i] != nullptr) {
                            // a piece has been found that is not a rook, therefore castle is not valid
                            break;
                        }
                    }
                }

                if(!king->getMove() && (newPos.posY == king->getY() - 2)) {
                cout << "king has moved!" << endl;
            
                
                // check if king has been moved before and the selected position is two spaces to the right of king
                if(!king->getMove() && (newPos.posY == king->getY() + 2)) {            
                    
                    // check if king is at least at position f 
                    if((king->getY() > 6) && !king->getMove()) {

                        // iterate through the left side of the king to find a rook, if pieces are found, castle is not possible
                        for(int i = king->getY() + 2; i < 8; ++i) {
                            if(grid[king->getX()][i] != nullptr && grid[king->getX()][i]->getType() == Piece::ROOK) {
                                // if rook has been found, check if it has been moved
                                Rook *rook = dynamic_cast<Rook*>(grid[king->getX()][i]);

                                if(!rook->getMove()) {
                                    // if it hasn't been moved and there are no pieces, in the way, castle is valid
                                    cout << "Entering rook condition" << endl;
                                    grid[king->getX()][i] = nullptr;
                                    Position newTempPos{newPos.posX,newPos.posY - 1};
                                    grid[newTempPos.posX][newTempPos.posY] = rook;
                                    rook->setPosition(newTempPos);
                                    delete grid[king->getX()][i];
                                    rook->setMove();
                                }

                                break;
                            } else if(grid[king->getX()][i] != nullptr) {
                                // a piece has been found that is not a rook, therefore castle is not valid
                                break;
                            }
                        }
                    }
        
                }            
        
            } // end of if statement
            
            } 
        
        } // end of king check
        
        // Clear the piece's previous position on the board
        grid[p->getX()][p->getY()] = nullptr;

        // Capture handling if there is a piece at newPos
        if (grid[newPos.posX][newPos.posY] != nullptr) {
            delete grid[newPos.posX][newPos.posY]; 
        }

        // Move the piece to the new position
        grid[newPos.posX][newPos.posY] = p;

        Position tempPos = {p->getX(), p->getY()};

        // Update the piece's internal position
        p->setPosition(newPos);

        if(grid[p->getX()][p->getY()] != nullptr && grid[newPos.posX][newPos.posY]->getType() == Piece::KING) {
           King *king = dynamic_cast<King*>(p);
           if(!king->getMove()) { 
            king->setMove(); 
           }
        }

        if(grid[p->getX()][p->getY()] != nullptr && grid[p->getX()][p->getY()]->getType() == Piece::ROOK) {
                    
            Rook *rook = dynamic_cast<Rook*>(p);
            if(!rook->getMove()) {
                rook->setMove();
            }

        }

        // en passant is valid after it has been moved twice ///////// -------> change grid[newPos.posX][newPos.posY] to just p
        if(grid[p->getX()][p->getY()] != nullptr && grid[newPos.posX][newPos.posY]->getType() == Piece::PAWN) {
            
            Pawn *pawn = dynamic_cast<Pawn*>(p);
            pawn->setMove();


            // make sure to test this... seems a little off
            if(pawn->getToggle() && (newPos.posX == pawn->getX() + 2)) {
                pawn->setEnpassantTrue();
                pawn->setToggle();
            } else {
                pawn->setEnpassantFalse();
            }

        }
             
            
        if(p->getType() == Piece::PAWN && (grid[p->getX() - 1][p->getY()] != nullptr) 
                && (p->getColour() == "white" && (grid[p->getX() - 1][p->getY()]->getType() == Piece::PAWN))) {
                delete grid[p->getX() - 1][p->getY()];
                grid[p->getX() - 1][p->getY()] = nullptr;
        }
                
            
        if(p->getType() == Piece::PAWN && (grid[p->getX() + 1][p->getY()] != nullptr) 
                && (p->getColour() == "black" && (grid[p->getX() + 1][p->getY()]->getType() == Piece::PAWN))) {
                delete grid[p->getX() + 1][p->getY()];
                grid[p->getX() + 1][p->getY()] = nullptr;
        }
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
   
Position Board::findKingPosition(string colour) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const auto& piecePtr = grid[row][col];
            if (piecePtr && piecePtr->getColour() == colour && piecePtr->getType() == Piece::KING) {
                return {row, col};
            }
        }
    }
}

// Method to check if p1's king is currently in check
bool Board::isCheck(string playerColour) const {
    // Find the positions of the white and black kings
    Position kingPos = {-1, -1};
    kingPos = findKingPosition(playerColour);
    vector<Position> possibleMoves;
    
    // Check if any piece can capture the king 
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() != Piece::Type::KING) && (grid[i][j]->getColour() != playerColour)) {
                // See if any possible move of the piece is the same as the king's position
                possibleMoves = grid[i][j]->getPossibleMoves(); 
                for (const auto& move : possibleMoves) {
                    if (move.posX == kingPos.posX && move.posY == kingPos.posY) {
                        return true; // P1's King is in check
                    }
                }
            }
        }
    }

    return false; // P1's King is not in check
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
		turn = 1;
	} else if(turn == 1) {
		turn = 0;
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

Board::~Board() {
    clearBoard();
}
