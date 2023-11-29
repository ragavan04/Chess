#include "king.h"
#include "board.h"


King::King(Type pieceType, string colour, Position pos, Board& board)
    : Piece(pieceType, colour, pos, board) {}


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
                moves.push_back(newPos);
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

