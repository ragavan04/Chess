#include "controller.h"
// #include "board.h"
#include "textdisplay.h"
using namespace std;

Controller::Controller() : theBoard{new Board}, isWin{false}, player1Score{0}, player2Score{0}, gameInProgress{false} {}

Controller::~Controller() {
    theBoard->clearBoard();
}

void Controller::run(){
    string command;
    Player* player1;
    Player* player2;
    
    while (cin >> command) {

        // Parse and execute commands
        if (command == "game") {
            string whitePlayer;
            string blackPlayer;
            cin >> whitePlayer;
            cin >> blackPlayer;

            // Validate whitePlayer and blackPlayer
            bool validWhitePlayer = (whitePlayer == "human") || (whitePlayer.find("computer") == 0 && whitePlayer.size() == 11 && isdigit(whitePlayer[9]) && whitePlayer[9] >= '1' && whitePlayer[9] <= '4');
            bool validBlackPlayer = (blackPlayer == "human") || (blackPlayer.find("computer") == 0 && blackPlayer.size() == 11 && isdigit(blackPlayer[9]) && blackPlayer[9] >= '1' && blackPlayer[9] <= '4');
            
            if (!validWhitePlayer || !validBlackPlayer) {
                cerr << "Invalid player type. Player must be 'human' or 'computer[1-4]'." << endl;
                continue;
            } else {
                cout << "White: " << whitePlayer << " Black: " << blackPlayer << endl;
                if (whitePlayer.find("computer") == 0){
                    int whiteDifficulty = whitePlayer[9] - '0';
                    cout << "White player difficulty: " << whiteDifficulty << endl;
                } 
                if (blackPlayer.find("computer") == 0){
                    int blackDifficulty = blackPlayer[9] - '0';
                    cout << "Black player difficulty: " << blackDifficulty << endl;
                } 
            }

            if (whitePlayer == "human"){
                player1 = new Human{"white", "human"};
            } else {
                // create computer
            }

            if (blackPlayer == "human"){
                player2 = new Human{"black", "human"};
            } else {
                // create computer
            }

            theBoard->notifyObservers();
            cout << *theBoard;


            // Start a new game
            gameInProgress = true;
            cout << "Enter 'setup' to place your own pieces. Enter 'standard' to use a standard chess board" << endl;

            
            
        } else if (command == "resign") {
            if (gameInProgress){
                // print board
                theBoard->notifyObservers();
                cout << *theBoard << endl;

                // check for player 1 resign
                if (theBoard->getTurn() == 0){
                    cout << "Player 1 resigns" << endl;
                    cout << "Black Wins!" << endl;
                    player2Score += 1;
                } 


                // check for player 2 resign
                if (theBoard->getTurn() == 1){
                    cout << "Player 2 resigns" << endl;
                    cout << "White Wins!" << endl;
                    player1Score += 1;
                }
                displayScore();
                theBoard->clearBoard();
                cout << "New game started" << endl;

            } else {
                cout << "No game in progress, cannot end game" << endl;
            }
            
            gameInProgress = false;

        } else if (command == "move") {
            // checking if there is a game in progress
            if (!gameInProgress){
                cerr << "Cannot make move. No game in progress." << endl;
                continue;
            }

            // if ((curPiece != nullptr) && (curPiece->isValid(tempEndPos))){
            //     theBoard->makeMove(curPiece, tempEndPos);
            // } else {
            //     cout << "Invalid move. Try a different move" << endl;
            // }


            // player 1 turn control
            if (theBoard->getTurn() == 0 && player1->getPlayerType() == "human") {
                cout << "inside white player:   " << endl;
                makeHumanMove("white", player1);
            // player 2 turn control
            } else if (theBoard->getTurn() == 1 && player2->getPlayerType() == "human") {
                cout << "inside black player" << endl;
                makeHumanMove("black", player2);
            }

            theBoard->switchTurns(); // switching the turn
        } else if (command == "setup") {
            cout << "inside setup mode" << endl;
            setupMode(player1, player2);
            for (size_t i = 0; i < player1->getAvailablePieces().size(); ++i){
                cout << "Player 1 piece:  " << player1->getAvailablePieces()[i]->displayChar() << "position: " << "X: "<< player1->getAvailablePieces()[i]->getX() << "Y: " << player1->getAvailablePieces()[i]->getY() << endl;
            }

            cout << endl;

            for (size_t i = 0; i < player2->getAvailablePieces().size(); ++i){
                cout << "Player 2 piece:  " << player2->getAvailablePieces()[i]->displayChar() << "position: " << "X: "<< player2->getAvailablePieces()[i]->getX() << "Y: " << player2->getAvailablePieces()[i]->getY() << endl;
            }

            theBoard->notifyObservers();
            cout << *theBoard << endl;
        } else if (command == "standard"){
            theBoard->standardBoardSetup();
            theBoard->notifyObservers();
            cout << *theBoard << endl;


        } else if (command == "test"){
            theBoard->testBoardSetup();
            theBoard->notifyObservers();
            cout << *theBoard << endl;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    } 
}


// Player Controller::setupPlayer(const string playerType, Player::Colour colour) {
//     if (playerType == "human") {
//         return Player(/* parameters for human player */);
//     } else if (playerType.find("computer") == 0) {
//         // Extract difficulty level and create a computer player
//         int difficulty = std::stoi(playerType.substr(8)); // Assuming format "computerX"
//         return Player(/* parameters for computer player with difficulty */);
//     }
//     // if input is unrecognized, i.e not human or computer
//     return Player(/* parameters for invalid*/);
// }

void Controller::displayScore() const{
    cout << "Final Score:" << endl;
    cout << "White: " << player1Score << endl;
    cout << "Black: " << player2Score << endl;
}



void Controller::setupMode(Player* player1, Player* player2) {
    std::string setupCommand;
    cout << "Entering setup mode. Enter commands to place pieces or type 'done' to exit." << endl;
    while (getline(cin, setupCommand)) {
        if (setupCommand == "done") {
            cout << "Exiting setup mode." << endl;
            break;
        }
        processSetupCommand(setupCommand, player1, player2);
    }
}


void Controller::processSetupCommand(const string& command, Player* player1, Player* player2) {
    bool whitePlacing, blackPlacing;
    // Parse the command to extract piece type and position
    char action, piece;
    string letter_position;
    string colour;
    stringstream ss{command};
    ss >> action;
    if (action == '+') {
        ss >> piece >> letter_position;
    } else if (action == '-') {
        ss >> letter_position;
    } else if (action == '='){
        ss >> colour;
    }
    Position position = convertCoords(letter_position);
    
    if (action == '+' && (position.posX != -1 && position.posY != -1)) {
        // Add piece to the board
        if (whitePlacing){
            theBoard->addPiece(tolower(piece), position, player1);
            cout << "Piece added: " << piece << " Position: " << letter_position << endl;
        } else if (blackPlacing){
            theBoard->addPiece(toupper(piece), position, player2);
            cout << "Piece added: " << piece << " Position: " << letter_position << endl;
        } else {
            cout << "No colour selected to place pieces. Enter '= colour' to let a player place pieces" << endl;
        }
    
    } else if (action == '-' && (position.posX != -1 && position.posY != -1)) {
        if (whitePlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr && theBoard->getState()[position.posX][position.posY]->getColour() == "white"){
                theBoard->removePiece(position);
                cout << "piece remove: " << letter_position <<  endl;
            } else {
                cout << "Cannot remove a piece thats not yours or an empty position." << endl;
            }
        } 

        if (blackPlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr &&  theBoard->getState()[position.posX][position.posY]->getColour() == "black"){
                theBoard->removePiece(position);
                cout << "piece remove: " << letter_position <<  endl;
            } else {
                cout << "Cannot remove a piece thats not yours or an empty position." << endl;
            }
        }
        
    
    } else if (action == '='){
        if (colour == "white"){
            whitePlacing = true;
            blackPlacing = false;
        } else if (colour == "black"){
            whitePlacing = false;
            blackPlacing = true;
        } else {
            cout << "Invalid colour" << endl;
        }
    }
}

Position Controller::convertCoords(string coords) const{
    Position convertedCoords;
    istringstream iss{coords};
    char colChar;
    int row;

    iss >> colChar; // column letter
    iss >> row;     // row number
    //colChar = tolower(colChar); // make sure colChar is lowercase

    if (('a' <= colChar && colChar <= 'h') && (1 <= row && row <= 8)){
        // Convert 'a'-'h' to 0-7 (for columns)
        convertedCoords.posY = colChar - 'a';

        // Convert 1-8 to 0-7 (for rows), inverting the row order
        convertedCoords.posX = row - 1;
    } else {
        // signal error
        convertedCoords.posX = -1;
        convertedCoords.posY = -1;
        return convertedCoords; 
    }

    return convertedCoords;
}

void Controller::makeHumanMove(const string& playerColor, Player* player) {
    bool validMoveMade = false;
    bool validPromotionEntered = false;

    while (!validMoveMade) {
        string startPosition, endPosition;
        char promotionPiece;
        cin >> startPosition;
        if (startPosition == "move"){
            cin >> startPosition;
        }
        cin >> endPosition;
        Position tempStartPos = convertCoords(startPosition);
        Position tempEndPos = convertCoords(endPosition);

        cout << "Starting position: (" << tempStartPos.posX << "," << tempStartPos.posY << ")" << endl;
        cout << "Ending position: (" << tempEndPos.posX << "," << tempEndPos.posY << ")" << endl;
        
        if ((tempStartPos.posX == -1 && tempStartPos.posY == -1) || (tempEndPos.posX == -1 && tempEndPos.posY == -1)){
            cerr << "Position out of bounds. Select a position with column[a-h] and row[1-8]" << endl;
            continue;
        }

        Piece* curPiece = theBoard->getState()[tempStartPos.posX][tempStartPos.posY];
        if (curPiece != nullptr && curPiece->isValid(tempEndPos) && curPiece->getColour() == playerColor) {

            // pawn promotion logic
            if ((curPiece->getType() == Piece::PAWN) && playerColor == "white" && tempEndPos.posX == 7 || (curPiece->getType() == Piece::PAWN) && playerColor == "black" && tempEndPos.posX == 0){               
                while(!validPromotionEntered){
                    cin >> promotionPiece;
                    if (promotionPiece == 'N' || promotionPiece == 'n' || promotionPiece == 'R' || promotionPiece == 'r' || promotionPiece == 'Q' || promotionPiece == 'q' || promotionPiece == 'B' || promotionPiece == 'b' || promotionPiece == 'P' || promotionPiece == 'p'){
                        validPromotionEntered = true;
                    } else {
                        cout << "Enter valid promotion" << endl;
                        continue;
                    }                    
                }

                theBoard->removePiece(tempStartPos);
                // check if player is white, if so add piece for white player
                if (playerColor == "white"){
                    theBoard->addPiece(tolower(promotionPiece), tempEndPos, player);
                } 

                // check if player is black, if so add piece for black player
                if (playerColor == "black"){
                    theBoard->addPiece(toupper(promotionPiece), tempEndPos, player);
                }
            } else {
                // make the move inputted
                theBoard->makeMove(curPiece, tempEndPos);
            }

            validMoveMade = true;
        } else {
            cout << "Invalid move." << endl;
        }
    }

    theBoard->notifyObservers();
    cout << *theBoard << endl;
}


