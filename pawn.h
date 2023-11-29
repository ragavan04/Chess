#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn : public Piece {

    bool moved;

public:
    Pawn(Type pieceType, string colour, Position pos, Board& board);

    // Override the getPossibleMoves method for the Pawn
    vector<Position> getPossibleMoves() const override;

    // Override the isValid method for the Pawn

    char displayChar() const;
};

#endif
