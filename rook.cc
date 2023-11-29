#include "rook.h"


Rook::Rook(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board) {}




vector<Position> Rook::getPossibleMoves() const {

    string oppColour;
    vector<Position> temp; 

    if(getColour() == "white") {
        oppColour == "black";
    } else if(getColour() == "black") {
        oppColour == "white";
    }
    

    // checking west side of rook
    for(int i = pos.posX; i > 0; --i) {

        if(theBoard.getState()[i][pos.posY] == nullptr) {
            Position tempPos{i,pos.posY};
            temp.push_back(tempPos);
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() == oppColour) {
            Position tempPos{i,pos.posY};
            temp.push_back(tempPos);
            break;
        } else {
            break;
        }
    }

    // checking east side of rook
    for(int i = pos.posX; i < 8; ++i) {

        if(theBoard.getState()[i][pos.posY] == nullptr) {
            Position tempPos{i,pos.posY};
            temp.push_back(tempPos);
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() == oppColour) {
            Position tempPos{i,pos.posY};
            temp.push_back(tempPos);
            break;
        } else {
            break;
        }
    }

    // checking north side of rook
    for(int i = pos.posY; i > 0; --i) {

        if(theBoard.getState()[pos.posX][i] == nullptr) {
            Position tempPos{pos.posX,i};
            temp.push_back(tempPos);
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == oppColour) {
            Position tempPos{pos.posX,i};
            temp.push_back(tempPos);
            break;
        } else {
            break;
        }
    }

    // checking north side of rook
    for(int i = pos.posY; i < 8; ++i) {

        if(theBoard.getState()[pos.posX][i] == nullptr) {
            Position tempPos{pos.posX,i};
            temp.push_back(tempPos);
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == oppColour) {
            Position tempPos{pos.posX,i};
            temp.push_back(tempPos);
            break;
        } else {
            break;
        }
    }

    return temp;
}



char Rook::displayChar() const {
        
    if(getColour() == "white") {
        return 'r';
    } else if(getColour() == "black") {
        return 'R';
    }
    
    
}





