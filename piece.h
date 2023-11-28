#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "board.h"

using namespace std;

struct Position{ int posX; int posY; };

class Piece{
    
    private:
         

    public:
        enum Type { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };
        
    protected:
        Type pieceType;
        Position pos;
        string colour;
        unique_ptr<Board> theBoard;
        vector<Position> moves;
        

    public:
        Piece(Type pieceType, string colour, Position pos, unique_ptr<Board> board)
            : pieceType(pieceType), colour(colour), pos(pos), theBoard(std::move(board)) {}

        // Accessor methods
        int getX() const { return pos.posX; }
        int getY() const { return pos.posY; }
        void setPosition(unique_ptr<Position> position) { 
            pos.posX = position.get()->posX; 
            pos.posY = position.get()->posY;
        }
        Type getType() const { return pieceType; }

        vector<Position> getPossibleMoves() const; 
        bool isValid(Position newPos) const; // pure virtual methods, to be implemented within each piece
        char displayChar() const; // will return a char for each piece type (eg. 'p' for pawn), used in displaying the board
        ~Piece() {}; // virtual dtor
};


/////////////////////////////////////// MAKE THESE VIRTUAL LATER


#endif


