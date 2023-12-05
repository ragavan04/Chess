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
        Position findKingPosition(string colour) const; // returns the location of 
        bool isCheck(string colour);
        bool isInCheckAfterMove(Position currPos, Position newPos, string colour);
        Position getPositionCausingCheck(string playerColour);
        bool isStalemate(string playerColour);
        bool canBlock(Position attacker, Position target, string playerColour);
        bool canCapture(Position attacker, Position target);
        bool isCheckmate(string playerColour);
        vector<vector<Piece*>> getState() const; // returns the grid
        void notifyObservers(int srcRow, int srcCol, int destRow, int destCol); // notifies observers of changes made to the board
        void attach(View *o);
        void clearBoard();
        ~Board();
         
        friend ostream& operator<<(ostream& out, const Board& board);
};


#endif



