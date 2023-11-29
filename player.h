#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "piece.h"

using namespace std;

class Player{
    protected:
        string colour;
        vector<Piece*> availablePieces;
        vector<Piece*> lostPieces;
        vector<pair<Piece*, Position>> availableMoves;
    public:
        Player(const string& colour) : colour{colour} {}

        // Acessor methods
        const Piece* getAvailablePiece(int index) const { return availablePieces[index]; }
        void setColour(string newColour) { colour = newColour; }
        string getColour() const { return colour; }
        vector<pair<Piece*, Position>> getAvailableMoves() { return availableMoves; }

        void addMoves(const Piece* p);
        virtual ~Player() {}; // virtual dtor   
};


#endif


