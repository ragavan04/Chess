#include "piece.h"
#include "board.h"

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
            for (const auto& move : possibleMoves) {
                if (move.posX == newPos.posX && move.posY == newPos.posY) {
                    return true; // newPos exists in possibleMoves vector
                }
            }
            return false; // newPos doesn't exist in possibleMoves vector
        } 