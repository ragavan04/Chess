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
        bool isValid(Position newPos) const { // Returns a bool based on if the given position is valid
            // Create vector of positions with all possible moves
            vector<Position> possibleMoves = getPossibleMoves();
            for (const auto& move : possibleMoves) {
                if (move.posX == newPos.posX && move.posY == newPos.posY) {
                    return true; // newPos exists in possibleMoves vector
                }
            }
            return false; // newPos doesn't exist in possibleMoves vector
        } 
        virtual char displayChar() const = 0; // will return a char for each piece type (eg. 'p' for pawn), used in displaying the board
        ~Piece() {}; // virtual dtor
};


/////////////////////////////////////// MAKE THESE VIRTUAL LATER


#endif


