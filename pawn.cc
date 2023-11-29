#include "pawn.h"
#include "board.h"


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

    // if the pawn is white, it can only move down on the board
    if(getColour() == "white") { 
        if(!moved && theBoard.getState()[pos.posX + 2][pos.posY] == nullptr) {
            Position tempPos{pos.posX + 2,pos.posY};
            temp.push_back(tempPos);        
        }

        if(theBoard.getState()[pos.posX + 1][pos.posY] == nullptr) {
            Position tempPos{pos.posX + 1,pos.posY};
            temp.push_back(tempPos);      
        }
 
    

    //     // check for capture move on top left corner
    //     if(theBoard.getState()[pos.posX - 1][pos.posY - 1] != nullptr && 
    //         theBoard.getState()[pos.posX - 1][pos.posY - 1]->getColour() == oppColour) {
    //             Position tempPos{pos.posX - 1,pos.posY - 1};
    //             temp.push_back(tempPos);
    //     } 

    //     // check for capture move on top left corner
    //     if(theBoard.getState()[pos.posX + 1][pos.posY - 1] != nullptr && 
    //         theBoard.getState()[pos.posX + 1][pos.posY - 1]->getColour() == oppColour) {
    //             Position tempPos{pos.posX + 1,pos.posY - 1};
    //             temp.push_back(tempPos);
    //     }
    
    } 

    // if(getColour() == "white") { 
    //     if(!moved && theBoard.getState()[pos.posY - 2][pos.posX] == nullptr) {
    //         Position tempPos{pos.posY - 2,pos.posX};
    //         temp.push_back(tempPos);        
    //     }

    //     if(theBoard.getState()[pos.posY - 1][pos.posX] == nullptr) {
    //         Position tempPos{pos.posY - 1,pos.posX};
    //         temp.push_back(tempPos);        
    //     } 

    //     // check for capture move on top left corner
    //     if(theBoard.getState()[pos.posX + 1][pos.posY + 1] != nullptr && 
    //         theBoard.getState()[pos.posX + 1][pos.posY + 1]->getColour() == oppColour) {
    //             Position tempPos{pos.posX + 1,pos.posY + 1};
    //             temp.push_back(tempPos);
    //     } 

    //     // check for capture move on top left corner
    //     if(theBoard.getState()[pos.posX - 1][pos.posY + 1] != nullptr && 
    //         theBoard.getState()[pos.posX - 1][pos.posY + 1]->getColour() == oppColour) {
    //             Position tempPos{pos.posX - 1,pos.posY + 1};
    //             temp.push_back(tempPos);
    //     }
    // }  

    return temp;

}


char Pawn::displayChar() const {

    if(getColour() == "white") {
        return 'p';
    } else if(getColour() == "black") {
        return 'P';
    }

}



