#include "levelfive.h"

LevelFive::LevelFive(const std::string& colour, std::string playerType) 
    : LevelFour(colour, playerType), useOpeningBook(true) {
    loadOpeningBook();
}

void LevelFive::loadOpeningBook() {
    openingBook.push_back({ {0, 6}, {2, 5} }); // White's knight from g1 to f3
    openingBook.push_back({ {0, 1}, {2, 2} }); // White's knight from b1 to c3
    // openingBook.push_back({ {7, 1}, {5, 2} }); // Black's knight from b8 to c6
    // openingBook.push_back({ {7, 6}, {5, 5} }); // Black's knight from g8 to f6
    // Pawn structure-focused opening moves
    openingBook.push_back({ {1, 4}, {3, 4} }); // Double King's Pawn
    openingBook.push_back({ {6, 4}, {4, 4} });
    openingBook.push_back({ {1, 3}, {3, 3} }); // Double Queen's Pawn
    openingBook.push_back({ {6, 3}, {4, 3} });
    openingBook.push_back({ {1, 4}, {3, 4} }); // Sicilian Defense
    openingBook.push_back({ {6, 2}, {4, 2} });
    openingBook.push_back({ {1, 4}, {3, 4} }); // Caro-Kann Defense
    openingBook.push_back({ {6, 2}, {5, 2} });
    openingBook.push_back({ {1, 4}, {3, 4} }); // King's Indian Defense
    openingBook.push_back({ {6, 6}, {5, 6} });
    openingBook.push_back({ {1, 3}, {3, 3} }); // Queen's Gambit
    openingBook.push_back({ {6, 4}, {4, 4} });
    openingBook.push_back({ {1, 3}, {3, 3} }); // Slav Defense
    openingBook.push_back({ {6, 2}, {4, 2} });
    openingBook.push_back({ {1, 4}, {3, 4} }); // Ruy Lopez Opening
    openingBook.push_back({ {6, 4}, {5, 4} });
    // Common opening moves
    openingBook.push_back({ {1, 4}, {3, 4} }); // King's Pawn Opening
    openingBook.push_back({ {1, 3}, {3, 3} }); // Queen's Pawn Opening
    openingBook.push_back({ {1, 2}, {3, 2} }); // English Opening
    openingBook.push_back({ {1, 6}, {3, 6} }); // King's Indian Attack
    openingBook.push_back({ {6, 4}, {4, 4} }); // French Defense
    openingBook.push_back({ {6, 3}, {4, 3} }); // Queen's Gambit
    // Add more openings as needed
}



std::pair<Position, Position> LevelFive::selectOpeningMove(Board* board) const {
    for (auto it = openingBook.begin(); it != openingBook.end();) {
        const auto &move = *it;
        Piece* piece = board->getState()[move.first.posX][move.first.posY];
        if (piece != nullptr && piece->getColour() == this->getColour()) {
            if (piece->isValid(move.second)) {
                auto validMove = *it;
                it = openingBook.erase(it); // Remove the valid move from the book
                return validMove;
            } else {
                // Invalid move, remove it and continue
                it = openingBook.erase(it);
            }
        } else {
            // If piece is nullptr or not the right colour, skip this move
            ++it;
        }
    }

    // If no valid opening move is found, use LevelFour algorithm
    return LevelFour::algorithm(board);
}


std::pair<Position, Position> LevelFive::algorithm(Board* board) const {
    // Attempt to use an opening move if available
    if (useOpeningBook) {
        std::pair<Position, Position> openingMove = selectOpeningMove(board);
        if (openingMove.first.posX != -1) {
            // If a valid opening move is found, return it
            return openingMove;
        }
    }

    // Default to LevelFour's algorithm if not using the opening book or if no valid opening move is found
    return LevelFour::algorithm(board);
}

