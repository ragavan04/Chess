#include "queen.h"
#include "board.h"
using namespace std;

// Ctor for Queen
Queen::Queen(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board, 9) {}

// Returns a vector of possible positions that the Queen can move on the board
vector<Position> Queen::getPossibleMoves() const {
    // Create vector to be populated
    vector<Position> possibleMoves;

    // West
    for (int i = pos.posY - 1; i >= 0; --i) {
        if (theBoard.getState()[pos.posX][i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX, i });
        } else if (theBoard.getState()[pos.posX][i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX, i });
            break;
        } else {
            break;
        }
    }

    // East
    for (int i = pos.posY + 1; i < 8; ++i) {
        if (theBoard.getState()[pos.posX][i] == nullptr) {
            possibleMoves.push_back(Position{ pos.posX, i });
        } else if (theBoard.getState()[pos.posX][i]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ pos.posX, i });
            break;
        } else {
            break;
        }
    }

    // North
    for (int i = pos.posX - 1; i >= 0; --i) {
        if (theBoard.getState()[i][pos.posY] == nullptr) {
            possibleMoves.push_back(Position{ i, pos.posY });
        } else if (theBoard.getState()[i][pos.posY]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ i, pos.posY });
            break;
        } else {
            break;
        }
    }

    // South
    for (int i = pos.posX + 1; i < 8; ++i) {
        if (theBoard.getState()[i][pos.posY] == nullptr) {
            possibleMoves.push_back(Position{ i, pos.posY });
        } else if (theBoard.getState()[i][pos.posY]->getColour() != getColour()) {
            possibleMoves.push_back(Position{ i, pos.posY });
            break;
        } else {
            break;
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
