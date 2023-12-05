#include "levelfour.h"

LevelFour::LevelFour(const std::string& colour, std::string playerType) 
    : LevelThree(colour, playerType), useOpeningBook(true) {
    loadOpeningBook();
}

void LevelFour::loadOpeningBook() {
    openingBook.push_back({ {0, 6}, {2, 5} }); // White's knight from g1 to f3
    openingBook.push_back({ {0, 1}, {2, 2} }); // White's knight from b1 to c3
    // openingBook.push_back({ {7, 1}, {5, 2} }); // Black's knight from b8 to c6
    // openingBook.push_back({ {7, 6}, {5, 5} }); // Black's knight from g8 to f6
    // // Pawn structure-focused opening moves
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
    // // Common opening moves
    openingBook.push_back({ {1, 4}, {3, 4} }); // King's Pawn Opening
    openingBook.push_back({ {1, 3}, {3, 3} }); // Queen's Pawn Opening
    openingBook.push_back({ {1, 2}, {3, 2} }); // English Opening
    openingBook.push_back({ {1, 6}, {3, 6} }); // King's Indian Attack
    openingBook.push_back({ {6, 4}, {4, 4} }); // French Defense
    openingBook.push_back({ {6, 3}, {4, 3} }); // Queen's Gambit
    // // Add more openings as needed
}



std::pair<Position, Position> LevelFour::selectOpeningMove(Board* board) const {
    for (auto it = openingBook.begin(); it != openingBook.end();) {
        const auto &move = *it;
        Piece* piece = board->getState()[move.first.posX][move.first.posY];
        if (piece != nullptr && piece->getColour() == this->getColour()) {
            if (piece->isValid(move.second)) {
                cout << "USING OPENING MOVE" << endl;
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

    // If no valid opening move is found, use LevelThree algorithm
    cout << "NOT USING OPENING BOOK, USING LEVEL THREE ALGORITHM" << endl;
    return LevelThree::algorithm(board);
}




std::pair<Position, Position> LevelFour::algorithm(Board* board) const {
    // Check for an opening move
    std::pair<Position, Position> openingMove = { {-1, -1}, {-1, -1} };
    if (useOpeningBook) {
        openingMove = selectOpeningMove(board);
    }

    // If we have a valid opening move, check if it's better or equal to other moves
    if (openingMove.first.posX != -1) {
        int openingMoveScore = 8; // Score assigned to opening moves

        // Use LevelThree's algorithm to find the best move
        std::pair<Position, Position> bestLevelThreeMove = LevelThree::algorithm(board);
        int levelThreeMoveScore = LevelThree::evaluateMove(bestLevelThreeMove, board);

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
