#include "piece.h"
#include "board.h"
#include <iostream>

Piece::Piece(Type pieceType, string colour, Position pos, Board& board) 
            : pieceType(pieceType), colour(colour), pos(pos), theBoard(board) {}


int Piece::getX() const { return pos.posX; }
int Piece::getY() const { return pos.posY; }
void Piece::setPosition(const Position& position) { pos = position; }
string Piece::getColour() const { return colour; }
Piece::Type Piece::getType() const { return pieceType; }

bool Piece::isValid(Position newPos) const { // Returns a bool based on if the given position is valid
            // Create vector of positions with all possible moves
            vector<Position> possibleMoves = getPossibleMoves();
            if(possibleMoves.empty()) {
                cout << "Possible moves are empty" << endl;
            }
            for (const auto& move : possibleMoves) {
                cout << "Possible moves are: (" << move.posX << "," << move.posY << ")" << endl; 
                if (move.posX == newPos.posX && move.posY == newPos.posY) {
                    if (!theBoard.isInCheckAfterMove(Position{getX(), getY()}, newPos, getColour())) {
                        return true; // newPos exists in possibleMoves vector and does not put king in check
                    }
                }
            }
            return false; // newPos doesn't exist in possibleMoves vector
} 
