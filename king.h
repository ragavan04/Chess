#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King : public Piece {
public:
    King(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

    // Override the getPossibleMoves method for the Knight
    //vector<Position> getPossibleMoves() const override;

    // Override the isValid method for the Knight
    bool isValid(Position newPos) const override{
        return true;
    }

    char displayChar() const {
        return 'K';
    }
};

#endif