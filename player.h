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
        vector<Piece*> lostPieces;
        map<Position, Position> availableMoves; 
    public:
        Player(const string& colour) : colour{colour} {}

        // Acessor methods
        void setColour(string newColour) { colour = newColour; }
        string getColour() const { return colour; }
        void addToLostPieces(Piece* lostPiece) { lostPieces.push_back(lostPiece); }
        vector<Piece*> getLostPieces() { return lostPieces; }
        map<Position, Position> getAvailableMoves() { return availableMoves; }

        void addToAvailableMoves(Position startPos, Position endPost);
        virtual ~Player() {}; // virtual dtor   
};


#endif


