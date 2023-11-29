#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "board.h"

using namespace std;

class Board;
struct Position{ int posX; int posY; };

class Piece{
    
    public:
        enum Type { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };
        
    protected:
        Type pieceType;
        string colour;
        Position pos;
        Board& theBoard;
        

    public:
        Piece(Type pieceType, string colour, Position pos, Board& board) 
            : pieceType(pieceType), colour(colour), pos(pos), theBoard(board) {}

        // Accessor methods
        int getX() const { return pos.posX; }
        int getY() const { return pos.posY; }
        void setPosition(const Position& position) { pos = position; }
        string getColour() const { return colour; }
        Type getType() const { return pieceType; }

        virtual vector<Position> getPossibleMoves() const = 0; 
        virtual bool isValid(Position newPos) const = 0; // pure virtual methods, to be implemented within each piece
        virtual char displayChar() const = 0; // will return a char for each piece type (eg. 'p' for pawn), used in displaying the board
        ~Piece() {}; // virtual dtor
};


/////////////////////////////////////// MAKE THESE VIRTUAL LATER


#endif


