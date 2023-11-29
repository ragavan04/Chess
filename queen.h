#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"

class Queen : public Piece {
public:
    Queen(Type pieceType, string colour, Position pos, Board& board);

    // Override the getPossibleMoves method for the Queen
    vector<Position> getPossibleMoves() const override;

    // Override the isValid method for the Queen
    bool isValid(Position newPos) const override;

    char displayChar() const override;
};

#endif