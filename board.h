#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "view.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
class Piece;
class View;
using namespace std;


class Board {

    vector<vector<Piece*>> grid;
    int turn;
    bool isWin;
    //Player player1; 
    //Player player2; 
    vector<View*> views;

    public:
        Board();

        // bool isInCheckAfterMove(Position kingPos) const; // checks if the king is still in check after being in check in the previous turn
        // Position getPosition(const Piece p) const; // gets the position of a given piece
        // void switchTurns(); // switches the turn field
        // int whoWins() const ; // returns 1 if player 1 wins, returns 2 if player 2 wins
        // void boardInit(Piece p, Position pos, string action); // initalizes the board
        // bool getIsWin() const; // returns true if the board is a winning state, returns false is board is not in a winning state 
        // int getTurn() const; // returns the turn field
        // void addMoves(Piece p); // adds possible moves to the availableMoves vector
        // bool isCheckmate(Player &p) const; // checks if there is a checkmate present on the board
        // bool isCheck(Player &p); // checks if there is a check present on the board
        // bool isStalemate(Player &p) const; // checks if there is a stalemate present on the board
        void makeMove(Piece* p, Position pos); // makes a move on the board, for the piece p to the positon pos
        void addPiece(char type, Position pos);
        vector<vector<Piece*>> getState() const; // returns the grid
        // void clone(Piece::Type pieceType); // makes a clone of the given piece 
        void notifyObservers(); // notifies observers of changes made to the board
        void attach(View *o);
         
        ///Position findKingPosition(Player::Colour colour) const; // function to find the kings current position on the board
        friend ostream& operator<<(ostream& out, const Board& board);
};


#endif



