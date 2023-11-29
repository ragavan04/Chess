#include "queen.h"
using namespace std;

// Ctor for Knight
Knight::Knight(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

// Returns a vector of possible positions that the Knight can move on the board
vector<Position> Knight::getPossibleMoves() const {
    vector<Position> possibleMoves;
    int x = getX();
    int y = getY();
    int tempY = y;
    int tempX = x;

    // 2 Up, 1 Right
    tempY -= 2;
    ++tempX;
    if (tempY > -1 || tempX < 8) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 1 Up, 2 Right
    --tempY;
    tempX += 2;
    if (tempY > -1 || tempX < 8) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 2 Down, 1 Right
    tempY += 2;
    ++tempX;
    if (tempY < 8 || tempX < 8) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 1 Down, 2 Right
    ++tempY;
    tempX += 2;
    if (tempY < 8 || tempX < 8) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 2 Down, 1 Left
    tempY += 2;
    --tempX;
    if (tempY < 8 || tempX > -1) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 1 Down, 2 Left
    ++tempY;
    tempX -= 2;
    if (tempY < 8 || tempX > -1) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 2 Up, 1 Left
    tempY -= 2;
    --tempX;
    if (tempY > -1 || tempX > -1) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    // 1 Up, 2 Left
    --tempY;
    tempX -= 2;
    if (tempY > -1 || tempX > -1) {
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else if (theBoard.getState()[tempX][tempY]->getColour() != getColour()) {
            possibleMoves.push_back({tempX, tempY});
        }
    }
    tempY = y;
    tempX = x;

    return possibleMoves;
}

char Knight::displayChar() const {
    if (getColour() == "white") {
        return 'n';
    } else {
        return 'N';
    }
}
