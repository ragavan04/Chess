#include "knight.h"
#include "board.h"
using namespace std;

// Ctor for Knight
Knight::Knight(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

// Returns a vector of possible positions that the Knight can move on the board
vector<Position> Knight::getPossibleMoves() const {
    // Create vector to be populated
    vector<Position> possibleMoves;

    // Possible knight move offsets
    vector<pair<int, int>> directions = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for (const auto& offset : directions) {
        int newX = pos.posX + offset.first;
        int newY = pos.posY + offset.second;

        // Check if the new position is within the board boundaries
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the destination square is empty or occupied by an opponent's piece
            if (theBoard.getState()[newX][newY] == nullptr ||
                theBoard.getState()[newX][newY]->getColour() != getColour()) {
                possibleMoves.push_back(Position{ newX, newY });
            }
        }
    }

    return possibleMoves;
}

char Knight::displayChar() const {
    if (getColour() == "white") {
        return 'n';
    } else {
        return 'N';
    }
}
