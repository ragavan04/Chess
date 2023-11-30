#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
#include <map>

using namespace std;

class Player{
    protected:
        string colour;
        string playerType;
        vector<Piece*> lostPieces;
        map<Position, vector<Position>> availableMoves; 
    public:
        Player(const string& colour, string playerType) : colour{colour}, playerType{playerType}{}

        // Acessor methods
        void setColour(string newColour) { colour = newColour; }
        string getColour() const { return colour; }
        string getPlayerType() const { return playerType; }
        void addToLostPieces(Piece* lostPiece) { lostPieces.push_back(lostPiece); }
        vector<Piece*> getLostPieces() { return lostPieces; }
        map<Position, vector<Position>> getAvailableMoves() { return availableMoves; }

        void addToAvailableMoves(Piece* piece);
        virtual ~Player() {}; // virtual dtor   
};


#endif


