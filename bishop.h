#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(Type pieceType, string colour, Position pos, Board& board);

    vector<Position> getPossibleMoves() const override;

    char displayChar() const override;
};

#endif
