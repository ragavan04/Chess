#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight : public Piece {
public:
    Knight(Type pieceType, string colour, Position pos, Board& board);

    // Override the getPossibleMoves method for the Knight
    vector<Position> getPossibleMoves() const override;

    char displayChar() const override;
};

#endif