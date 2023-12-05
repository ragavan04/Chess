#include "levelfour.h"

LevelFour::LevelFour(const std::string& colour, std::string playerType) 
    : LevelThree(colour, playerType), useOpeningBook(true) {
    loadOpeningBook();
}

void LevelFour::loadOpeningBook() {
    // Add your opening moves here
    openingBook.push_back({ {1, 4}, {3, 4} });
    openingBook.push_back({ {1, 0}, {2, 0} });
    // ... other opening moves
}

std::pair<Position, Position> LevelFour::selectOpeningMove() const {
    if (!openingBook.empty()) {
        auto move = openingBook.front();
        openingBook.erase(openingBook.begin()); // Remove the used move
        return move;
    }
    return { {-1, -1}, {-1, -1} };
}

std::pair<Position, Position> LevelFour::algorithm(Board* board) const {
    // Check for an opening move
    std::pair<Position, Position> openingMove = { {-1, -1}, {-1, -1} };
    if (useOpeningBook) {
        openingMove = selectOpeningMove();
    }

    // If we have a valid opening move, check if it's better or equal to other moves
    if (openingMove.first.posX != -1) {
        int openingMoveScore = 8; // Score assigned to opening moves

        // Use LevelThree's algorithm to find the best move
        std::pair<Position, Position> bestLevelThreeMove = LevelThree::algorithm(board);
        int levelThreeMoveScore = LevelThree::evaluateMoveThree(bestLevelThreeMove, board);

        // Compare the scores
        if (levelThreeMoveScore <= openingMoveScore) {
            return openingMove; // Use opening move if it's better or equal
        } else {
            return bestLevelThreeMove; // Use LevelThree move otherwise
        }
    }

    // If no opening move or if opening move is not good enough, use LevelThree logic
    return LevelThree::algorithm(board);
}
