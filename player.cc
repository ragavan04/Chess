#include "player.h"
#include "board.h"
#include <iostream>

Player::Player(const std::string& colour, std::string playerType) 
    : colour(colour), playerType(playerType) {}

void Player::setColour(std::string newColour) {
    colour = newColour;
}

std::string Player::getColour() const {
    return colour;
}

std::string Player::getPlayerType() const {
    return playerType;
}

void Player::addToLostPieces(Piece* lostPiece) {
    lostPieces.push_back(lostPiece);
}

std::vector<Piece*> Player::getLostPieces() const {
    return lostPieces;
}

std::map<Position, std::vector<Position>> Player::getAvailableMoves() const {
    return availableMoves;
}

void Player::renderAvailableMoves(Board* board) {
    availableMoves.clear(); // Clearing the existing moves

    for (int x = 0; x < 8; x++) { 
        for (int y = 0; y < 8; y++) {
            Position pos = {x, y};
            Piece* piece = board->getState()[x][y];
            if (piece != nullptr && piece->getColour() == this->getColour()) {
                // Get possible moves for this piece
                vector<Position> moves = piece->getPossibleMoves();
                // Add to the map
                availableMoves[pos] = moves;
            }
        }
    }  
}

// void Player::renderAvailableMoves(Board* board) {
//     availableMoves.clear(); // Clearing the existing moves

//     bool kingInCheck = board->isCheck(this->getColour());

//     for (int x = 0; x < 8; x++) { 
//         for (int y = 0; y < 8; y++) {
//             Position pos = {x, y};
//             Piece* piece = board->getState()[x][y];
//             if (piece != nullptr && piece->getColour() == this->getColour()) {
//                 vector<Position> moves = piece->getPossibleMoves();
//                 vector<Position> validMoves;

//                 for (const Position& move : moves) {
//                     if (!kingInCheck || board->isInCheckAfterMove(pos, move, this->getColour())) {
//                         validMoves.push_back(move);
//                     }
//                 }

//                 if (!validMoves.empty()) {
//                     availableMoves[pos] = validMoves;
//                 }
//             }
//         }
//     }  
// }



void Player::printAvailableMoves() const {
    for (const auto& pair : availableMoves) {
        const Position& startPos = pair.first;
        const std::vector<Position>& endPositions = pair.second;

        std::cout << "Start Position: (" << startPos.posX << ", " << startPos.posY << ")\n";
        std::cout << "Possible End Positions: ";
        for (const auto& endPos : endPositions) {
            std::cout << "(" << endPos.posX << ", " << endPos.posY << ") ";
        }
        std::cout << std::endl;
    }
}

bool Player::hasPlacedKing() const {
    return pieceCount.find('k') != pieceCount.end() && pieceCount.at('k') > 0;
}

bool Player::addPieceType(char piece) {
     // Define the standard chess piece counts
    unordered_map<char, int> standardCounts = {{'k', 1}, {'q', 1}, {'r', 2}, {'b', 2}, {'n', 2}, {'p', 8}};

    // Increment the count for this piece
    pieceCount[tolower(piece)]++;
    cout << "incrementing...." << endl;
    cout << "colour: "   << colour << endl;
    
    
    // Check if the count exceeds the standard amount
    if (pieceCount[tolower(piece)] > standardCounts[tolower(piece)]) {

        pieceCount[tolower(piece)]--;  // Undo the addition
        return false;  // Indicate that the addition was not allowed
    }

    return true;  // Indicate successful addition
}

Player::~Player() {
    // Assuming lostPieces holds dynamically allocated Piece objects
    for (auto piece : lostPieces) {
        delete piece;
    }
    lostPieces.clear();
}
