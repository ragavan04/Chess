#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
// #include "board.h"

using namespace std;

class Board;

struct Position{ 
    int posX; 
    int posY; 
    bool operator<(const Position& other) const {
        if (posX == other.posX) return posY < other.posY;
        return posX < other.posX;
    }
    friend bool operator==(const Position& lhs, const Position& rhs) {
        return lhs.posX == rhs.posX && lhs.posY == rhs.posY;
    }

};

class Piece{
    
    public:
        enum Type { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };
        
    protected:
        Type pieceType;
        string colour;
        Position pos;
        Board& theBoard;
        int score;
        

    public:
        Piece(Type pieceType, string colour, Position pos, Board& board, int score);

        // Accessor methods
        int getX() const;
        int getY() const;
        void setPosition(const Position& position);
        string getColour() const;
        Type getType() const;
        int getScoreValue() const;

        virtual vector<Position> getPossibleMoves() const = 0;
        bool isValid(Position newPos) const;
        virtual char displayChar() const = 0; // will return a char for each piece type (eg. 'p' for pawn), used in displaying the board
        virtual ~Piece() {}; // virtual dtor
};




#endif


