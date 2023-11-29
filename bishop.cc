#include "bishop.h"

vector<Position> Bishop::getPossibleMoves() const {
    vector<Position> possibleMoves;
    int x = getX();
    int y = getY();
    int north = getY();
    int east = getX();
    int south = 7 - getY();
    int west = 7 - getX();
    int tempY = y;
    int tempX = x;

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
