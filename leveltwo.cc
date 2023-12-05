#include "leveltwo.h"
#include "computer.h"
#include <utility>
#include <random>

using namespace std;

LevelTwo::LevelTwo(const string& colour, string playerType) : LevelOne(colour,playerType) {}


pair<Position, Position> LevelTwo::algorithm(Board* board) const {
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
    int firstMoveScore = evaluateMoveTwo(possibleMoves[0],board);
    maxScore = firstMoveScore;

    for (const auto &move : possibleMoves) {
        int moveScore = evaluateMoveTwo(move, board);
        if (moveScore > maxScore) {
            maxScore = moveScore;
            bestMove = move;
        }
    }

    if(firstMoveScore == maxScore) {
         LevelOne::algorithm(board);
    }


    return bestMove;
}




int LevelTwo::evaluateMoveTwo(const pair<Position, Position> &move, Board* board) const {

    Position start = move.first;
    Position end = move.second;
    Piece* movingPiece = board->getState()[start.posX][start.posY];
    Piece* targetPiece = board->getState()[end.posX][end.posY];
    int captureScore = 0;

    // Score for capturing a piece
    if (targetPiece != nullptr && movingPiece != nullptr && board->canCapture(start,end) && targetPiece->getColour() != movingPiece->getColour()) {
        captureScore += targetPiece->getScoreValue();
    }

    return captureScore;


}





