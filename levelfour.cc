#include "levelfour.h"

LevelFour::LevelFour(const std::string& colour, std::string playerType) 
    : LevelThree(colour, playerType), useOpeningBook(true) {
    loadOpeningBook();
}

void LevelFour::loadOpeningBook() {
    openingBook.push_back({ {1, 4}, {3, 4} });
    openingBook.push_back({ {1, 2}, {3, 2} });
    // Add more openings as needed
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
    if (useOpeningBook) {
        auto openingMove = selectOpeningMove();
        if (openingMove.first.posX != -1) {
            return openingMove;
        }
        useOpeningBook = false;
    }
    return LevelThree::algorithm(board);
}
