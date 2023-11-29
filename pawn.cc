#include "pawn.h"



Pawn::Pawn(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board), moved{false} {}


vector<Position> Pawn::getPossibleMoves() const {

    string oppColour;
    vector<Position> temp; 

    if(getColour() == "white") {
        oppColour == "black";
    } else if(getColour() == "black") {
        oppColour == "white";
    }
    
    if(!moved && theBoard.getState()[pos.posX][pos.posY - 2] == nullptr) {
        Position tempPos{pos.posX,pos.posY - 2};
        temp.push_back(tempPos);        
    } 
    
    if(theBoard.getState()[pos.posX][pos.posY - 1] == nullptr) {
        Position tempPos{pos.posX,pos.posY - 1};
        temp.push_back(tempPos);        
    }

    // check for capture move on top left corner
    if(theBoard.getState()[pos.posX - 1][pos.posY - 1] != nullptr && 
        theBoard.getState()[pos.posX - 1][pos.posY - 1]->getColour() == oppColour) {
            Position tempPos{pos.posX - 1,pos.posY - 1};
            temp.push_back(tempPos);
    } 

    // check for capture move on top left corner
    if(theBoard.getState()[pos.posX + 1][pos.posY - 1] != nullptr && 
        theBoard.getState()[pos.posX + 1][pos.posY - 1]->getColour() == oppColour) {
            Position tempPos{pos.posX + 1,pos.posY - 1};
            temp.push_back(tempPos);
    }

    return temp;

}


char Pawn::displayChar() const {

    if(getColour() == "white") {
        return 'p';
    } else if(getColour() == "black") {
        return 'P';
    }

}



