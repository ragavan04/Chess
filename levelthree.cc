#include "levelthree.h"
using namespace std;

LevelThree::LevelThree(const string& colour, string playerType) : LevelTwo(colour, playerType) {}

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
    int firstMoveScore = evaluateMove(possibleMoves[0],board);
    maxScore = firstMoveScore;

    for (const auto &move : possibleMoves) {
        int moveScore = evaluateMove(move, board);
        if (moveScore > maxScore) {
            maxScore = moveScore;
            bestMove = move;
        }
    }

    if(firstMoveScore == maxScore) {
        bestMove = LevelTwo::algorithm(board);
    }


    return bestMove;
}

int LevelThree::evaluateMove(const pair<Position, Position> &move, Board* board) const {

    int avoidScore = 0;
    Position start = move.first;
    Position end = move.second;
    Piece* movingPiece = board->getState()[start.posX][start.posY];
    Piece* targetPiece = board->getState()[end.posX][end.posY];
    int captureScore = 0;
    int checkScore = 0;
    string oppColour;

    // Score for capturing a piece
    if (targetPiece != nullptr && movingPiece != nullptr && board->canCapture(start,end) && targetPiece->getColour() != movingPiece->getColour()) {
        captureScore += targetPiece->getScoreValue();
    }

    // Score for avoiding capture
    if (avoidsCapture(move, board, movingPiece->getColour())) {
        avoidScore = movingPiece->getScoreValue();
    }

    if(movingPiece->getColour() == "white") {
        oppColour = "black";
    } else if(movingPiece->getColour() == "black") {
       oppColour = "white"; 
    }

    if (movingPiece != nullptr && movingPiece->getType() == Piece::KING && !board->isInCheckAfterMove(move.first, move.second, oppColour)) {
        return 1000;
    }

    // Score for checking the opponent's king
    if (movingPiece != nullptr && movingPiece->getType() != Piece::KING && board->isInCheckAfterMove(move.first, move.second, oppColour)) {
        checkScore += 20;
    }

    if(captureScore <= avoidScore) {
        return avoidScore;
    } else if(captureScore > avoidScore) {
        return captureScore;
    } else if(captureScore <= checkScore) {
        return checkScore;
    } else if(captureScore > checkScore) {
        return captureScore;
    } else if(avoidScore <= checkScore) {
        return checkScore;
    } else if(avoidScore > checkScore) {
        return avoidScore;
    }


}


bool LevelThree::avoidsCapture(const pair<Position, Position> &move, Board* board, const string& playerColour) const {

    // Check if any opponent's piece can capture the moved piece
    bool isSafe = true;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* potentialAttacker = board->getState()[x][y];
            if (potentialAttacker != nullptr && potentialAttacker->getColour() != playerColour) {
               Position attackerPosition = {x, y};
                if (board->canCapture(attackerPosition,move.first)) {
                    isSafe = false;
                    break;
                }
            }
        }
        if (!isSafe) break;
    }

    return isSafe;

}


