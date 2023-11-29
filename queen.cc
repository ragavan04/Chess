#include "queen.h"
using namespace std;

// Ctor for Queen
Queen::Queen(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}

// Returns a vector of possible positions that the Queen can move on the board
vector<Position> Queen::getPossibleMoves() const { 
    vector<Position> possibleMoves;
    int x = getX();
    int y = getY();
    int north = getY();
    int east = getX();
    int south = 7 - getY();
    int west = 7 - getX();
    int tempY = y;
    int tempX = x;

    // North
    for (int i = north; i > 0; --i) {
        --tempY;
        if (theBoard.getState()[x][tempY] == nullptr) {
            possibleMoves.push_back({x, tempY});
        } else {
            if (theBoard.getState()[x][tempY]->getColour() == getColour()) {
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({x, tempY});
                tempY = y;
                break;
            }
        }
    }

    // East
    for (int i = east; i > 0; --i) {
        ++tempX;
        if (theBoard.getState()[tempX][y] == nullptr) {
            possibleMoves.push_back({tempX, y});
        } else {
            if (theBoard.getState()[tempX][y]->getColour() == getColour()) {
                tempX = x;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                break;
            }
        }
    }

    // South
    for (int i = south; i > 0; --i) {
        ++tempY;
        if (theBoard.getState()[x][tempY] == nullptr) {
            possibleMoves.push_back({x, tempY});
        } else {
            if (theBoard.getState()[x][tempY]->getColour() == getColour()) {
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({x, tempY});
                tempY = y;
                break;
            }
        }
    }

    // West
    for (int i = west; i > 0; --i) {
        --tempX;
        if (theBoard.getState()[tempX][y] == nullptr) {
            possibleMoves.push_back({tempX, y});
        } else {
            if (theBoard.getState()[tempX][y]->getColour() == getColour()) {
                tempX = x;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                break;
            }
        }
    }

    // North-East
    while (tempX < 7 || tempY > 0) {
        ++tempX;
        --tempY;
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else {
            if (theBoard.getState()[tempX][tempY]->getColour() == getColour()) {
                tempX = x;
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                tempY = y;
                break;
            }
        }
    }

    // South-East
    while (tempX < 7 || tempY < 7) {
        ++tempX;
        ++tempY;
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else {
            if (theBoard.getState()[tempX][tempY]->getColour() == getColour()) {
                tempX = x;
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                tempY = y;
                break;
            }
        }
    }

    // South-West
    while (tempX > 0 || tempY < 7) {
        --tempX;
        ++tempY;
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else {
            if (theBoard.getState()[tempX][tempY]->getColour() == getColour()) {
                tempX = x;
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                tempY = y;
                break;
            }
        }
    }

    // North-West
    while (tempX > 0 || tempY > 0) {
        --tempX;
        --tempY;
        if (theBoard.getState()[tempX][tempY] == nullptr) {
            possibleMoves.push_back({tempX, tempY});
        } else {
            if (theBoard.getState()[tempX][tempY]->getColour() == getColour()) {
                tempX = x;
                tempY = y;
                break;
            } else {
                possibleMoves.push_back({tempX, y});
                tempX = x;
                tempY = y;
                break;
            }
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
