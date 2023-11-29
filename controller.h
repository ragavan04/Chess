#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "board.h"

using namespace std;

class Controller{
    Board* theBoard;
    // Player player1;
    // Player player2;
    View* TD;
    // unique_ptr<View> GD; 
    bool isWin;
    int player1Score;
    int player2Score;
    bool gameInProgress;

    public:
    	Controller();
        ~Controller();
        // void startGame(unique_ptr<Player> player1, unique_ptr<Player> player2);
        // Player setupPlayer(const string playerType, Colour colour);
        Position convertCoords(string coords) const;
        void displayScore() const;
        // unique_ptr<Piece> makePiece(char c, Piece::Position pos);
        void run();
        void setupMode();
        void processSetupCommand(const std::string& command);
};





#endif
