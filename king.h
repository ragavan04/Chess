#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King : public Piece {
    bool moved;
public:
    King(Type pieceType, string colour, Position pos, Board& board);

    vector<Position> getPossibleMoves() const override;
    bool getMove() { return moved; }
    void setMove() { moved = true; }
    char displayChar() const override;
};

#endif

