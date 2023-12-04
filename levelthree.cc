#include "levelthree.h"
#include <utility>
#include <set>


using namespace std;

LevelThree::LevelThree(const string& colour, string playerType) : Computer(colour, playerType) {}

pair<Position, Position> LevelThree::algorithm(Board* board) const {
    auto availableMovesMap = getAvailableMoves();
    vector<std::pair<Position, Position>> possibleMoves;

    // Converting map<Position, vector<Position>> to vector<pair<Position, Position>>
    for (const auto& movePair : availableMovesMap) {
        Position start = movePair.first;
        for (const Position& end : movePair.second) {
            possibleMoves.emplace_back(start, end);
        }
    }

    int maxScore = -1;
    std::pair<Position, Position> bestMove;

    for (const auto &move : possibleMoves) {
        int moveScore = evaluateMove(move, board);
        if (moveScore > maxScore) {
            maxScore = moveScore;
            bestMove = move;
        }
    }

    return bestMove;
}


int LevelThree::evaluateMove(const std::pair<Position, Position> &move, Board* board) const {
    int score = 0;
    Position start = move.first;
    Position end = move.second;
    Piece* movingPiece = board->getState()[start.posX][start.posY];
    Piece* targetPiece = board->getState()[end.posX][end.posY];

    // Score for capturing a piece
    if (targetPiece != nullptr && targetPiece->getColour() != movingPiece->getColour()) {
        score += targetPiece->getScoreValue();
    }

    // Score for avoiding capture
    if (moveAvoidsCapture(move, board, movingPiece->getColour())) {
        if (movingPiece->getType() == Piece::PAWN){
            score += 1;
        } else if (movingPiece->getType() == Piece::KING){
            score += 15;
        } else if (movingPiece->getType() == Piece::QUEEN) {
            score += 10;
        } else {
            score += 5;
        }
        
    }

    // Score for checking the opponent's king
    if (board->isInCheckAfterMove(move.first, move.second, movingPiece->getColour())) {
        score += 12;
    }

    return score;
}

bool LevelThree::moveAvoidsCapture(const std::pair<Position, Position> &move, Board* board, const std::string& playerColour) const {
    Piece* movedPiece = board->getState()[move.first.posX][move.first.posY];

    // Temporarily make the move
    board->makeMove(movedPiece, move.second);

    // Check if any opponent's piece can capture the moved piece
    bool isSafe = true;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* potentialAttacker = board->getState()[x][y];
            if (potentialAttacker != nullptr && potentialAttacker->getColour() != playerColour) {
                Position attackerPosition = {x, y};
                if (board->canCapture(attackerPosition, move.second)) {
                    isSafe = false;
                    break;
                }
            }
        }
        if (!isSafe) break;
    }

    // Revert the move
    board->undoMove(move.first, move.second);

    return isSafe;
}

