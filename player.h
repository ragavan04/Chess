#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
#include <map>
#include <unordered_map>
#include "board.h"

class board;
using namespace std;

class Player{
    protected:
        string colour;
        string playerType;
        unordered_map<char, int> pieceCount;
        vector<Piece*> lostPieces;
        map<Position, vector<Position>> availableMoves; 
    public:
        Player(const string& colour, string playerType);

        // Acessor methods
        void setColour(string newColour);
        string getColour() const;
        string getPlayerType() const;
        void addToLostPieces(Piece* lostPiece);
        vector<Piece*> getLostPieces() const;
        map<Position, vector<Position>> getAvailableMoves() const;
        
        void renderAvailableMoves(Board* board);

        void printAvailableMoves() const;
    
        bool hasPlacedKing() const;

        bool addPieceType(char piece);

        virtual int getComputerLevel() const { return 0; } // Default implementation for non-computer players

        virtual ~Player(); // virtual dtor   
};


#endif


