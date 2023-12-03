#include "rook.h"
#include "board.h"


Rook::Rook(Type pieceType, string colour, Position pos, Board& board)
        : Piece(pieceType, colour, pos, board), moved{false} {}





vector<Position> Rook::getPossibleMoves() const {

    string oppColour;
    vector<Position> temp; 

    
    ////////////// INCLUDE CASTLING

    // checking west side of rook
    for(int i = pos.posX - 1; i >= 0; --i) {
        Position tempPos;
        tempPos.posX = i;
        tempPos.posY = pos.posY;
        
        if(theBoard.getState()[i][pos.posY] == nullptr) {    
            temp.push_back(tempPos); 
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() != colour) {
            temp.push_back(tempPos); 
            cout << "capture piece found" << endl;
            break;
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() == colour) {
            cout << "own piece found piece found" << endl; 
            break;
        } 
    }

    // checking east side of rook
    for(int i = pos.posX + 1; i < 8; ++i) {
        Position tempPos;
        tempPos.posX = i;
        tempPos.posY = pos.posY;
        
        if(theBoard.getState()[i][pos.posY] == nullptr) {
            temp.push_back(tempPos); 
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() != colour) {
            temp.push_back(tempPos);
            cout << "capture piece found" << endl; 
            break;
        } else if(theBoard.getState()[i][pos.posY] != nullptr && theBoard.getState()[i][pos.posY]->getColour() == colour) {
            cout << "own piece found piece found" << endl;
            break;
        }
    }

    // checking north side of rook
    for(int i = pos.posY - 1; i >= 0; --i) {

        Position tempPos;
        tempPos.posX = pos.posX;
        tempPos.posY = i;
        
        if(theBoard.getState()[pos.posX][i] == nullptr) {
            temp.push_back(tempPos); 
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() != colour) {
            temp.push_back(tempPos);
            cout << "capture piece found" << endl;  
            break;
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == colour) {
            cout << "own piece found piece found" << endl;
            break;
        }
    }

    // checking south side of rook
    for(int i = pos.posY + 1; i < 8; ++i) {

        Position tempPos;
        tempPos.posX = pos.posX;
        tempPos.posY = i;
        
        if(theBoard.getState()[pos.posX][i] == nullptr) {
            temp.push_back(tempPos); 
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() != colour) {
            temp.push_back(tempPos); 
            cout << "capture piece found" << endl; 
            break;
        } else if(theBoard.getState()[pos.posX][i] != nullptr && theBoard.getState()[pos.posX][i]->getColour() == colour) {
            cout << "own piece found piece found" << endl;
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





