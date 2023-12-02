#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
#include <map>
#include <unordered_map>

using namespace std;

class Player{
    protected:
        string colour;
        string playerType;
        unordered_map<char, int> pieceCount;
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
        
        bool hasPlacedKing() const {
            return pieceCount.find('k') != pieceCount.end() && pieceCount.at('k') > 0;
        }

        bool addPieceType(char piece) {
            // Define the standard chess piece counts
            unordered_map<char, int> standardCounts = {{'k', 1}, {'q', 1}, {'r', 2}, {'b', 2}, {'n', 2}, {'p', 8}};

            // Increment the count for this piece
            pieceCount[tolower(piece)]++;
            cout << "incrementing...." << endl;
            cout << "colour: "   << colour << endl;
            
            
            // Check if the count exceeds the standard amount
            if (pieceCount[tolower(piece)] > standardCounts[tolower(piece)]) {

                pieceCount[tolower(piece)]--;  // Undo the addition
                return false;  // Indicate that the addition was not allowed
            }

            return true;  // Indicate successful addition
        }


        virtual ~Player() {}; // virtual dtor   
};


#endif


