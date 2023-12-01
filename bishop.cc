#include "bishop.h"
#include "board.h"

Bishop::Bishop(Type pieceType, string colour, Position pos, Board& board)
    : Piece(pieceType, colour, pos, board) {}

vector<Position> Bishop::getPossibleMoves() const {
    vector<Position> possibleMoves;

    // Diagonal moves (upper left)
    for (int i = 1; pos.posX - i >= 0 && pos.posY - i >= 0; ++i) {
        if (theBoard.getState()[pos.posX - i][pos.posY - i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY - i });
        } else if (theBoard.getState()[pos.posX - i][pos.posY - i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY - i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (upper right)
    for (int i = 1; pos.posX - i >= 0 && pos.posY + i < 8; ++i) {
        if (theBoard.getState()[pos.posX - i][pos.posY + i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY + i });
        } else if (theBoard.getState()[pos.posX - i][pos.posY + i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY + i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (lower left)
    for (int i = 1; pos.posX + i < 8 && pos.posY - i >= 0; ++i) {
        if (theBoard.getState()[pos.posX + i][pos.posY - i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY - i });
        } else if (theBoard.getState()[pos.posX + i][pos.posY - i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY - i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (lower right)
    for (int i = 1; pos.posX + i < 8 && pos.posY + i < 8; ++i) {
        if (theBoard.getState()[pos.posX + i][pos.posY + i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY + i });
        } else if (theBoard.getState()[pos.posX + i][pos.posY + i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY + i });
            break;
        } else {
            break;
        }
    }

    return possibleMoves;
}


char Bishop::displayChar() const{
    if(getColour() == "white"){
        return 'b';
    } else {
        return 'B';
    }
}

