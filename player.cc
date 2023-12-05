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
    availableMoves.clear(); // Clear previous moves

    // Iterate through all positions on the board
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Position currentPosition = {x, y};
            Piece* currentPiece = board->getState()[x][y];

            // Check if there's a piece at the current position and it belongs to the player
            if (currentPiece && currentPiece->getColour() == this->colour) {
                vector<Position> validMoves;

                // Get all possible moves for the piece
                vector<Position> possibleMoves = currentPiece->getPossibleMoves();

                // Validate each possible move
                for (const auto& move : possibleMoves) {
                    if (!board->isInCheckAfterMove(currentPosition, move, this->colour)) {
                        validMoves.push_back(move);
                    }
                }

                // If there are valid moves, add them to the map
                if (!validMoves.empty()) {
                    availableMoves[currentPosition] = validMoves;
                }
            }
        }
    }
}



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
    cout << "colour: "   << colour << endl;
    
    
    // Check if the count exceeds the standard amount
    if (pieceCount[tolower(piece)] > standardCounts[tolower(piece)]) {

        pieceCount[tolower(piece)]--;  // Undo the addition
        return false;  // Indicate that the addition was not allowed
    }

    return true;  // Indicate successful addition
}

void Player::removePieceType(Piece::Type piece){
    char p;
    if (piece == Piece::Type::BISHOP){
        p = 'b';
    } else if (piece == Piece::Type::KING){
        p = 'k';
    } else if (piece == Piece::Type::QUEEN){
        p = 'q';
    } else if (piece == Piece::Type::PAWN){
        p = 'p';
    } else if (piece == Piece::Type::KNIGHT){
        p = 'n';
    } else if (piece == Piece::Type::ROOK){
        p = 'r';
    } 
    --pieceCount[piece];
}

Player::~Player() {
    // Assuming lostPieces holds dynamically allocated Piece objects
    for (auto piece : lostPieces) {
        delete piece;
    }
    lostPieces.clear();
}
