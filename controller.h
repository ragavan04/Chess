#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "levelfive.h"
#include "graphicsdisplay.h"

using namespace std;

class Controller{
    Board* theBoard;
    View* TD;
    // unique_ptr<View> GD; 
    bool isWin;
    float player1Score;
    float player2Score;
    bool gameInProgress;
    bool whitePlacing;
    bool blackPlacing;

    public:
    	Controller();
        ~Controller();
        Position convertCoords(string coords) const; // converts the input coordinates to coordinates we can use to access pieces on the board
        void displayScore() const; // displays the score of both players when quiting the program
        void run(); // runs the game of chess
        void setupMode(Player* player1, Player* player2); // enters setup mode when players wish to customize the locations of their piece
        void processSetupCommand(const string& command, Player* player1, Player* player2); // processing 
        void makeHumanMove(const string& playerColor, Player* player);
        void makeComputerMove(const string& playerColour, Player* player);
};





#endif
