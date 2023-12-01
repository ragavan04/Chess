#include "king.h"
#include "board.h"
#include "rook.h"


King::King(Type pieceType, string colour, Position pos, Board& board)
    : Piece(pieceType, colour, pos, board), moved{false} {}

bool isInCheckAfterMove(string colour, Position kingPos, Board& board) {
    string oppColour = (colour == "white") ? "black" : "white";
    vector<Position> tempMoves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.getState()[i][j] != nullptr) {
                if (board.getState()[i][j]->getColour() == oppColour) {
                    tempMoves = board.getState()[i][j]->getPossibleMoves();
                    for (Position move : tempMoves) {
                        if (move.posX == kingPos.posX && move.posY == kingPos.posY) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

vector<Position> King::getPossibleMoves() const {
    vector<Position> moves;
    vector<pair<int, int>> directions = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    for (const auto& dir : directions) {
        Position newPos;
        newPos.posX = this->pos.posX + dir.first;
        newPos.posY = this->pos.posY + dir.second;

        // Check if the new position is within the board boundaries
        if (newPos.posX >= 0 && newPos.posX < 8 && newPos.posY >= 0 && newPos.posY < 8) {
            Piece* pieceAtNewPos = theBoard.getState()[newPos.posX][newPos.posY];
            
            
            // Check if the position is either empty or has an opponent's piece
            if (pieceAtNewPos == nullptr || pieceAtNewPos->getColour() != this->colour) {
                if (!isInCheckAfterMove(colour, newPos, theBoard)) {
                    moves.push_back(newPos);
                }
            }
        }
    }

    
    if(!moved && (pos.posY > 1) && theBoard.getState()[pos.posX][pos.posY - 2] == nullptr) {

        for(int i = pos.posY - 1; i >= 0; --i) {
            if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == colour
                && theBoard.getState()[pos.posX][i]->getType() == Piece::ROOK) {

                Rook *rook = dynamic_cast<Rook*>(theBoard.getState()[pos.posX][i]);

                if(!rook->getMove()) {
                    Position temp{pos.posX,pos.posY - 2};
                    moves.push_back(temp);
                }
                break;
            } else if(theBoard.getState()[pos.posX][i] != nullptr) {
                break;
            }
        }

    }

    if(!moved && (pos.posY < 6) && theBoard.getState()[pos.posX][pos.posY + 2] == nullptr) {
        
        for(int i = pos.posY + 2; i < 8; ++i) {
            if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == colour
                && theBoard.getState()[pos.posX][i]->getType() == Piece::ROOK) {

                Rook *rook = dynamic_cast<Rook*>(theBoard.getState()[pos.posX][i]);

                if(!rook->getMove()) {
                    Position temp{pos.posX,pos.posY + 2};
                    moves.push_back(temp);
                }

                break;
            } else if(theBoard.getState()[pos.posX][i] != nullptr) {
                break;
            }
        }

    }

    return moves;
}

char King::displayChar() const {
    if(getColour() == "white"){
        return 'k';
    } else {
        return 'K';
    }
}

