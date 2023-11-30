#include "human.h"

Human::Human(const string& colour, string playerType) : Player(colour, playerType){}

void Human::addToAvailableMoves(Piece* piece){
    if ((piece != nullptr) && (piece->getColour() == colour)) { // Ensure piece is not null
        Position startPosition;
        startPosition.posX = piece->getX();
        startPosition.posY = piece->getY();

        vector<Position> endPositions = piece->getPossibleMoves();
        availableMoves[startPosition] = endPositions;
    }
}

