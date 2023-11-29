#include "queen.h"
#include "board.h"
using namespace std;

// Ctor for Queen
Queen::Queen(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

// Returns a vector of possible positions that the Queen can move on the board
vector<Position> Queen::getPossibleMoves() const {
    // Create vector to be populated
    vector<Position> possibleMoves;

    // Horizontal moves
    for (int i = 0; i < 8; ++i) {
        if (i != pos.posY) {
            if (theBoard.getState()[pos.posX][i] == nullptr) {
                possibleMoves.push_back(Position{ pos.posX, i }); // Horizontal move
            } else if (theBoard.getState()[pos.posX][i]->getColour() != getColour()) {
                possibleMoves.push_back(Position{ pos.posX, i }); // Horizontal move
                break;
            } else {
                break;
            }
        }
    }

    // Vertical moves
    for (int i = 0; i < 8; ++i) {
        if (i != pos.posX) {
            if (theBoard.getState()[i][pos.posY] == nullptr) {
                possibleMoves.push_back(Position{ i, pos.posY }); // Vertical move
            } else if (theBoard.getState()[i][pos.posY]->getColour() != getColour()) {
                possibleMoves.push_back(Position{ i, pos.posY }); // Vertical move
                break;
            } else {
                break;
            }
        }
    }

    // Diagonal moves (upper left)
    for (int i = 1; pos.posX - i >= 0 && pos.posY - i >= 0; ++i) {
        if (theBoard.getState()[pos.posX - i][pos.posY - i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY - i });
        } else if (theBoard.getState()[pos.posX - i][pos.posY - i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY - i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (upper right)
    for (int i = 1; pos.posX - i >= 0 && pos.posY + i < 8; ++i) {
        if (theBoard.getState()[pos.posX - i][pos.posY + i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY + i });
        } else if (theBoard.getState()[pos.posX - i][pos.posY + i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX - i, pos.posY + i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (lower left)
    for (int i = 1; pos.posX + i < 8 && pos.posY - i >= 0; ++i) {
        if (theBoard.getState()[pos.posX + i][pos.posY - i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY - i });
        } else if (theBoard.getState()[pos.posX + i][pos.posY - i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY - i });
            break;
        } else {
            break;
        }
    }

    // Diagonal moves (lower right)
    for (int i = 1; pos.posX + i < 8 && pos.posY + i < 8; ++i) {
        if (theBoard.getState()[pos.posX + i][pos.posY + i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY + i });
        } else if (theBoard.getState()[pos.posX + i][pos.posY + i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX + i, pos.posY + i });
            break;
        } else {
            break;
        }
    }

    return possibleMoves;
}

char Queen::displayChar() const {
    if (getColour() == "white") {
        return 'q';
    } else {
        return 'Q';
    }
}
