#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

    // Override the getPossibleMoves method for the Knight
    //vector<Position> getPossibleMoves() const override;

    // Override the isValid method for the Knight
    bool isValid(Position newPos) const override{
        return true;
    }

    char displayChar() const {
        return 'B';
    }
};

#endif