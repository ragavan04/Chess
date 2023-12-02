#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "graphicsdisplay.h"
// #include "window.h"
class Piece;
class Player;
class View;
class Position;
using namespace std;


class Board {

    vector<vector<Piece*>> grid;
    int turn;
    bool isWin;
    //Player player1; 
    //Player player2; 
    vector<View*> views;
    //Xwindow xw;

    public:
        Board();

        void standardBoardSetup();
        void testBoardSetup();
        // bool isInCheckAfterMove(Position kingPos) const; // checks if the king is still in check after being in check in the previous turn
        // Position getPosition(const Piece p) const; // gets the position of a given piece
        void switchTurns(); // switches the turn field
        // int whoWins() const ; // returns 1 if player 1 wins, returns 2 if player 2 wins
        // void boardInit(Piece p, Position pos, string action); // initalizes the board
        // bool getIsWin() const; // returns true if the board is a winning state, returns false is board is not in a winning state 
        int getTurn() const; // returns the turn field
        // void addMoves(Piece p); // adds possible moves to the availableMoves vector
        // bool isCheckmate(Player &p) const; // checks if there is a checkmate present on the board
        // bool isCheck(Player &p); // checks if there is a check present on the board
        // bool isStalemate(Player &p) const; // checks if there is a stalemate present on the board
        void makeMove(Piece* p, Position pos); // makes a move on the board, for the piece p to the positon pos
        void undoMove(Position startPos, Position endPos);
        void addPiece(char type, Position pos);
        void removePiece(Position pos);
        Position findKingPosition(string colour) const;
        bool isCheck(string colour);
        bool isInCheckAfterMove(Position currPos, Position newPos, string colour);
        vector<Position> getPositionsCausingCheck(string playerColour);
        bool isCheckmate(string playerColour);
        vector<vector<Piece*>> getState() const; // returns the grid
        // void clone(Piece::Type pieceType); // makes a clone of the given piece 
        void notifyObservers(); // notifies observers of changes made to the board
        void attach(View *o);
        void clearBoard();
        ~Board();
         
        ///Position findKingPosition(Player::Colour colour) const; // function to find the kings current position on the board
        friend ostream& operator<<(ostream& out, const Board& board);
};


#endif



