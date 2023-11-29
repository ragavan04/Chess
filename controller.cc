#include "controller.h"
// #include "board.h"
#include "textdisplay.h"
using namespace std;

Controller::Controller() : theBoard{new Board}, isWin{false}, player1Score{0}, player2Score{0}, gameInProgress{false} {}

void Controller::run(){
    string command;
    
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

            theBoard->notifyObservers();
            cout << *theBoard;


            // Start a new game
            gameInProgress = true;

            
            
        } else if (command == "resign") {
            cout << "inside resign" << endl;
            gameInProgress = false;

        } else if (command == "move") {
            // checking if there is a game in progress
            if (!gameInProgress){
                cerr << "Cannot make move. No game in progress." << endl;
                continue;
            }

            // keep prompting user until a vaild move is made
            //bool vaildMoveMade = false;
            //while(!vaildMoveMade){

                string cmd, startPostition, endPosition;
                cin >> startPostition >> endPosition;
                Position tempStartPos = convertCoords(startPostition); // converting given coords into ints
                Position tempEndPos = convertCoords(endPosition); // converting given coords into ints

                // checks if given coords are in bounds
                if ((tempStartPos.posX == -1 && tempStartPos.posY == -1) || (tempEndPos.posX == -1 && tempEndPos.posY == -1)){
                    cerr << "Position out of bounds. Select a position with column[a-h] and row[1-8]" << endl;
                    continue;
                }

                Piece* curPiece = theBoard->getState()[tempStartPos.posX][tempStartPos.posY];

                if ((curPiece != nullptr) && (curPiece->isValid(tempEndPos))){
                    theBoard->makeMove(curPiece, tempEndPos);
                } else {
                    cout << "Invalid move. Try a different move" << endl;
                }

                // // checking if its player 1's turn and if they are trying to move one of their own pieces
                // if (theBoard->getTurn() == 0){ 
                //     if (curPiece->getColour() == "white"){
                //         // if the given move is vaild, then make the move
                //         if (curPiece->isValid(tempEndPos)){
                //             theBoard->makeMove(curPiece, tempEndPos);
                //             vaildMoveMade = true;
                //         } else {
                //             cout << "Invalid move. Try a different move" << endl;
                //         }
                //     }
                // // checking if its player 2's turn and if they are trying to move one of their own pieces
                // } else {
                //     if (curPiece->getColour() == "black"){
                //         // if the given move is vaild, then make the move
                //         if (curPiece->isValid(tempEndPos)){ // WE DONT NEED TYPE IN HERE, JUST USED BISHOP AS A TEMP
                //             theBoard->makeMove(curPiece, tempEndPos);
                //             vaildMoveMade = true;
                //         } else {
                //             cout << "Invalid move. Try a different move" << endl;
                //         }
                //     }
                // }
            //}



            cout << "inside move" << endl;
            theBoard->notifyObservers();
            cout << *theBoard << endl;
            theBoard->switchTurns(); // switching the turn

        } else if (command == "setup") {
            cout << "inside setput mode" << endl;
            setupMode();
            cout << "passed setup" << endl;
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



void Controller::setupMode() {
    std::string setupCommand;
    cout << "Entering setup mode. Enter commands to place pieces or type 'done' to exit." << endl;
    while (getline(cin, setupCommand)) {
        if (setupCommand == "done") {
            cout << "Exiting setup mode." << endl;
            break;
        }
        processSetupCommand(setupCommand);
    }
}


void Controller::processSetupCommand(const std::string& command) {
    // Parse the command to extract piece type and position
    char action, piece;
    string letter_position;
    stringstream ss{command};
    ss >> action;
    if (action == '+') {
        ss >> piece >> letter_position;
    } else if (action == '-') {
        ss >> letter_position;
    }
    Position position = convertCoords(letter_position);
    

    if (action == '+') {
        // Add piece to the board
        theBoard->addPiece(piece, position);
        cout << "piece added: " << piece << "pos: " << letter_position << endl;
    } else if (action == '-') {
        theBoard->removePiece(position);
        cout << "piece remove: " << letter_position <<  endl;
    }
}

Position Controller::convertCoords(string coords) const{
    Position convertedCoords;
    istringstream iss{coords};
    char colChar;
    int row;

    iss >> colChar; // column letter
    iss >> row;     // row number
    colChar = tolower(colChar); // make sure colChar is lowercase

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
