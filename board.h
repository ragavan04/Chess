#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "graphicsdisplay.h"
class Piece;
class Player;
class View;
class Position;
using namespace std;


class Board {

    vector<vector<Piece*>> grid;
    int turn;
    bool isWin;
    vector<View*> views;

    public:
        Board();

        void standardBoardSetup();
        void switchTurns(); // switches the turn field
        int getTurn() const; // returns the turn field
        void makeMove(Piece* p, Position pos); // makes a move on the board, for the piece p to the positon pos
        void undoMove(Piece* dup,bool captured, Position startPos, Position endPos); // undos the previous move 
        Piece* duplicate(Piece *p); // returns a piece pointer of a duplicate piece p
        void addPiece(char type, Position pos); // adds piece to the board during setup mode
        void removePiece(Position pos); // removes the piece during setup mode
        Position findKingPosition(string colour) const; // returns the location of colour's king
        bool isCheck(string colour); // returns true if the colour's king is in check
        bool isInCheckAfterMove(Position currPos, Position newPos, string colour); // returns true if colour's king is in check after a move has been done
        Position getPositionCausingCheck(string playerColour); // returns the position of the piece causing playerColour's king to be in check
        bool isStalemate(string playerColour); // returns true if the board is in a stalemate condition
        bool canBlock(Position attacker, Position target, string playerColour); // returns true if check can be clocked by playerColour's own piece
        bool canCapture(Position attacker, Position target); // returns true if own player's piece can take out the piece that puts their king in check
        bool isCheckmate(string playerColour); // returns true if the playerColour is facing a checkmate
        vector<vector<Piece*>> getState() const; // returns the grid
        void notifyObservers(int srcRow, int srcCol, int destRow, int destCol); // notifies observers of changes made to the board
        void attach(View *o); // attacks observers
        void clearBoard(); // clears the board
        ~Board();
         
        friend ostream& operator<<(ostream& out, const Board& board);
};


#endif



