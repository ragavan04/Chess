#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King : public Piece {
public:
    King(Type pieceType, string colour, Position pos, Board& board);

    vector<Position> getPossibleMoves() const override;

    char displayChar() const override;
};

#endif