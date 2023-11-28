#include "controller.h"
// #include "board.h"
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

            string cmd, startPostition, endPosition;
            cin >> startPostition >> endPosition;

            cout << "inside move" << endl;

        } else if (command == "setup") {
            cout << "inside setput mode" << endl;
            setupMode();
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
    ss >> action >> piece >> letter_position;
    

    if (action == '+') {
        // Add piece to the board
        cout << "piece added: " << piece << "pos: " << letter_position << endl;
    } else if (action == '-') {
        cout << "piece remove: " << letter_position <<  endl;
    }
}
