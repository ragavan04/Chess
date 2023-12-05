#include "controller.h"
// #include "board.h"
#include "textdisplay.h"
using namespace std;

Controller::Controller() : theBoard{new Board}, isWin{false}, player1Score{0}, player2Score{0}, gameInProgress{false}, whitePlacing(false), blackPlacing(false) {}

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
            int whiteDifficulty = 0;
            int blackDifficulty = 0;
            if (!validWhitePlayer || !validBlackPlayer) {
                cerr << "Invalid player type. Player must be 'human' or 'computer[1-4]'." << endl;
                continue;
            } else {
                cout << "White: " << whitePlayer << " Black: " << blackPlayer << endl;
                if (whitePlayer.find("computer") == 0){
                    whiteDifficulty = whitePlayer[9] - '0';
                    cout << "White player difficulty: " << whiteDifficulty << endl;
                } 
                if (blackPlayer.find("computer") == 0){
                    blackDifficulty = blackPlayer[9] - '0';
                    cout << "Black player difficulty: " << blackDifficulty << endl;
                } 
            }

            if (whitePlayer == "human"){
                player1 = new Human{"white", "human"};
                cout << "white human created" << endl;
            } else {
                if (whiteDifficulty == 1) {
                    player1 = new LevelOne{"white", "computer"};
                    cout << "white lvl 1 created" << endl;
                }
                if (whiteDifficulty == 3){
                    player1 = new LevelThree("white", "computer");
                    cout << "white lvl 3 created" << endl;
                }
                if (whiteDifficulty == 4){
                    player1 = new LevelFour("white", "computer");
                    cout << "white lvl 4 created" << endl;
                }
            }

            if (blackPlayer == "human"){
                player2 = new Human{"black", "human"};
                cout << "black human created" << endl;
            } else {
                if (blackDifficulty == 1) {
                    player2 = new LevelOne{"black", "computer"};
                    cout << "black lvl 1 created" << endl;
                }
                if (blackDifficulty == 3){
                    player2 = new LevelThree("black", "computer");
                    cout << "black lvl 3 created" << endl;
                }
                if (blackDifficulty == 4){
                    player2 = new LevelFour("black", "computer");
                    cout << "black lvl 4 created" << endl;
                }
            }

            theBoard->notifyObservers(0, 0, 0, 0);
            cout << *theBoard << endl;


            // Start a new game
            gameInProgress = true;
            cout << "Enter 'setup' to place your own pieces. Enter 'standard' to use a standard chess board" << endl;

            
            
        } else if (command == "resign") {
            if (gameInProgress){
                // print board
                theBoard->notifyObservers(0, 0, 0, 0);
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

            // player 1 turn control
            if (theBoard->getTurn() == 0) {
                // check if player 1 is a human
                if (player1->getPlayerType() == "human"){
                    cout << "inside white player:   " << endl;
                    makeHumanMove("white", player1);
                }
                // check if player 1 is a computer
                if (player1->getPlayerType() == "computer"){
                    makeComputerMove("white", player1);
                }
            
            // player 2 turn control
            } else if (theBoard->getTurn() == 1) {
                // check if player 2 is a human
                if (player2->getPlayerType() == "human"){
                    cout << "inside black player" << endl;
                    makeHumanMove("black", player2);
                }
                // check if player 2 is a comptuer
                if (player2->getPlayerType() == "computer"){
                    makeComputerMove("black", player2);
                }
            }

            
            if (theBoard->isCheckmate("white")){
                cout << "Checkmate! Black wins!" << endl;
                ++player2Score;
                theBoard->clearBoard();
                cout << "New game started" << endl;
                continue;
            }

            
            if (theBoard->isCheckmate("black")){
                cout << "Checkmate! White wins!" << endl;
                ++player1Score;
                theBoard->clearBoard();
                cout << "New game started" << endl;
                continue;
            }

            if (theBoard->isCheck("white")){
                cout << "White is in check" << endl; 
            } 

            if (theBoard->isCheck("black")){
                cout << "Black is in check" << endl;
            }
            
            if (theBoard->isStalemate("white") || theBoard->isStalemate("black")){
                cout << "Stalemate" << endl; 
                player1Score += 0.5;
                player1Score += 0.5;
            }

            player1->renderAvailableMoves(theBoard);
            player2->renderAvailableMoves(theBoard);
                       
            
            /*PRINTING OUT ALL MOVES!!!!
            cout << "player 1 availble moves:" << endl;
            player1->printAvailableMoves();
            cout << endl << endl;
            cout << "player 2 availble moves:" << endl;
            player2->printAvailableMoves();
            */


            theBoard->switchTurns(); // switching the turn
        } else if (command == "setup") {
            cout << "inside setup mode" << endl;
            if (player1 != nullptr && player2 != nullptr){
                setupMode(player1, player2);
                player1->renderAvailableMoves(theBoard);
                player2->renderAvailableMoves(theBoard);
            } else {
                cout << "1 or more player not initalized" << endl;
            }
        } else if (command == "standard"){
            if (player1 != nullptr && player2 != nullptr){
                theBoard->standardBoardSetup();
                player1->renderAvailableMoves(theBoard);
                player2->renderAvailableMoves(theBoard);
                theBoard->notifyObservers(0, 0, 0, 0);
                cout << *theBoard << endl;
            } else {
                cout << "1 or more player not initalized" << endl;
            }


        } else if (command == "test"){
            theBoard->testBoardSetup();
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    } 
}


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
            
            // Check if both players have placed at least one king and are under the standard piece count
            if (!player1->hasPlacedKing() || !player2->hasPlacedKing()) {
                cout << "Each player must place at least one King." << endl;
                continue; // Stay in setup mode
            }

            cout << "Exiting setup mode." << endl;
            break;
        }
        processSetupCommand(setupCommand, player1, player2);
    }
    whitePlacing = false;
    blackPlacing = false;
}


void Controller::processSetupCommand(const string& command, Player* player1, Player* player2) {   
    // Parse the command to extract piece type and position
    char action, piece;
    string letter_position;
    string colour;
    stringstream ss{command};
    ss >> action;
    if (action == '+') {
        if (!whitePlacing && !blackPlacing) {
            cout << "Please select a colour first." << endl;
            return;
        }
        ss >> piece >> letter_position;
    } else if (action == '-') {
        if (!whitePlacing && !blackPlacing) {
            cout << "Please select a colour first." << endl;
            return;
        }
        ss >> letter_position;
    } else if (action == '='){
        ss >> colour;
    }

    Position position = convertCoords(letter_position);
    
    if (action == '='){
        if (colour == "white"){
            whitePlacing = true;
            blackPlacing = false;
        } else if (colour == "black"){
            whitePlacing = false;
            blackPlacing = true;
        } else {
            cout << "Invalid colour" << endl;
        }
    } else if (action == '+' && (position.posX != -1 && position.posY != -1)) {
        // Check if the piece can be added based on the count
        
        bool canAddPiece = false;
        if ((whitePlacing && !blackPlacing) && !((piece == 'p' || piece == 'P') && (position.posX == 0 || position.posX == 7)) && player1->addPieceType(piece)) canAddPiece = true;
        if ((blackPlacing && !whitePlacing) && !((piece == 'p' || piece == 'P') && (position.posX == 0 || position.posX == 7)) && player2->addPieceType(piece)) canAddPiece = true;

        if ((piece == 'p' || piece == 'P') && (position.posX == 0 || position.posX == 7)){
            cout << "Cannot place pawn at row 1 or row 8" << endl;
            return;
        } else if (!canAddPiece) {
            cout << "Exceeded the standard amount for this piece type." << endl;
            return;
        }
        
        // Add piece to the board
        if (whitePlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr){
                theBoard->removePiece(position);
            }
            theBoard->addPiece(tolower(piece), position);
            if (theBoard->isCheck("black") || theBoard->isCheck("white")){
                theBoard->removePiece(position);
                cout << "Cannot place king in check in setup. Piece is not added." << endl;
            }
            theBoard->notifyObservers(0, 0, position.posX, position.posY);
            cout << *theBoard << endl;
            cout << "Piece added: " << piece << " Position: " << letter_position << endl;
        } else if (blackPlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr){
                theBoard->removePiece(position);
            }
            theBoard->addPiece(toupper(piece), position);
            if (theBoard->isCheck("black") || theBoard->isCheck("white")){
                theBoard->removePiece(position);
                cout << "Cannot place king in check in setup. Piece is not added." << endl;
            }
            theBoard->notifyObservers(0, 0, position.posX, position.posY);
            cout << *theBoard << endl;
            cout << "Piece added: " << piece << " Position: " << letter_position << endl;
        } else {
            cout << "No colour selected to place pieces. Enter '= colour' to let a player place pieces" << endl;
        }
    
    } else if (action == '-' && (position.posX != -1 && position.posY != -1)) {
        if (whitePlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr && theBoard->getState()[position.posX][position.posY]->getColour() == "white"){
                theBoard->removePiece(position);
                player1->removePieceType(theBoard->getState()[position.posX][position.posY]->getType());
                theBoard->notifyObservers(0, 0, position.posX, position.posY);
                cout << *theBoard << endl;
                cout << "piece remove: " << letter_position <<  endl;
            } else {
                cout << "Cannot remove a piece thats not yours or an empty position." << endl;
            }
        } 

        if (blackPlacing){
            if (theBoard->getState()[position.posX][position.posY] != nullptr &&  theBoard->getState()[position.posX][position.posY]->getColour() == "black"){
                theBoard->removePiece(position);
                player1->removePieceType(theBoard->getState()[position.posX][position.posY]->getType());
                cout << "piece remove: " << letter_position <<  endl;
                theBoard->notifyObservers(0, 0, position.posX, position.posY);
                cout << *theBoard << endl;
            } else {
                cout << "Cannot remove a piece thats not yours or an empty position." << endl;
            }
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
    Position tempStartPos = {0, 0};
    Position tempEndPos = {0, 0};

    while (!validMoveMade) {
        string startPosition, endPosition;
        char promotionPiece;
        cin >> startPosition;
        if (startPosition == "move"){
            cin >> startPosition;
        }
        cin >> endPosition;
        tempStartPos = convertCoords(startPosition);
        tempEndPos = convertCoords(endPosition);

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
                    theBoard->addPiece(tolower(promotionPiece), tempEndPos);
                } 

                // check if player is black, if so add piece for black player
                if (playerColor == "black"){
                    theBoard->addPiece(toupper(promotionPiece), tempEndPos);
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
    theBoard->notifyObservers(tempStartPos.posX, tempStartPos.posY, tempEndPos.posX, tempEndPos.posY);
    cout << *theBoard << endl;
}


void Controller::makeComputerMove(const string& playerColour, Player* player){
    int computerLevel = player->getComputerLevel();
    cout << playerColour << "(Computer Level " << computerLevel << ")." << endl;
    Position startingPos;
    Position endingPos;

    if (computerLevel == 1){
        LevelOne* levelOneComputer = dynamic_cast<LevelOne*>(player);
        if (levelOneComputer != nullptr) {
            // player is a Level1Computer
            pair<Position, Position>  move = levelOneComputer->algorithm(theBoard);
            
            startingPos = move.first;  // get the position of the piece to be moved
            endingPos = move.second; // get the ending position of the piece to be moved
            cout << "START POS X: " << startingPos.posX << "  Y:  " << startingPos.posY << endl;
            cout << "ending pos X: " << endingPos.posX << "  Y:  " << endingPos.posY << endl;
            Piece* curPiece = theBoard->getState()[startingPos.posX][startingPos.posY];
            
            theBoard->makeMove(curPiece, endingPos);        
        } 
    }

    if (computerLevel == 3){
         LevelThree* levelThreeComputer = dynamic_cast<LevelThree*>(player);
        if (levelThreeComputer != nullptr) {
            // player is a Level1Computer
            pair<Position, Position>  move = levelThreeComputer->algorithm(theBoard);
            
            startingPos = move.first;  // get the position of the piece to be moved
            endingPos = move.second; // get the ending position of the piece to be moved
            cout << "START POS X: " << startingPos.posX << "  Y:  " << startingPos.posY << endl;
            cout << "ending pos X: " << endingPos.posX << "  Y:  " << endingPos.posY << endl;
            Piece* curPiece = theBoard->getState()[startingPos.posX][startingPos.posY];
            
            theBoard->makeMove(curPiece, endingPos);        
        } 
    }

    if (computerLevel == 4){
         LevelFour* levelFourComputer = dynamic_cast<LevelFour*>(player);
        if (levelFourComputer != nullptr) {
            // player is a Level1Computer
            pair<Position, Position>  move = levelFourComputer->algorithm(theBoard);
            
            Position startingPos = move.first;  // get the position of the piece to be moved
            Position endingPos = move.second; // get the ending position of the piece to be moved
            cout << "START POS X: " << startingPos.posX << "  Y:  " << startingPos.posY << endl;
            cout << "ending pos X: " << endingPos.posX << "  Y:  " << endingPos.posY << endl;
            Piece* curPiece = theBoard->getState()[startingPos.posX][startingPos.posY];
            cout << "reached" << endl;
            if (curPiece != nullptr) {
                cout << "Current Piece: " << curPiece->displayChar() << endl;
                theBoard->makeMove(curPiece, endingPos);
            } else {
                cout << "No piece at starting position (" << startingPos.posX << ", " << startingPos.posY << ")" << endl;
            }

        theBoard->makeMove(curPiece, endingPos);        
        } 
    }
    theBoard->notifyObservers(startingPos.posX, startingPos.posY, endingPos.posX, endingPos.posY);
    cout << *theBoard << endl;
}



