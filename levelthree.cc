#include "levelthree.h"
#include <utility>
#include <set>
#include <random>


using namespace std;

LevelThree::LevelThree(const string& colour, string playerType) : LevelTwo(colour, playerType) {}

pair<Position, Position> LevelThree::algorithm(Board* board) const {
    auto availableMovesMap = getAvailableMoves();
    vector<std::pair<Position, Position>> possibleMoves;

    for (const auto& movePair : availableMovesMap) {
        Position start = movePair.first;
        for (const Position& end : movePair.second) {
            possibleMoves.emplace_back(start, end);
        }
    }

    int maxScore = -1;
    std::pair<Position, Position> bestMove;
    int firstMoveScore = evaluateMoveThree(possibleMoves[0],board);
    maxScore = firstMoveScore;

    for (const auto &move : possibleMoves) {
        int moveScore = evaluateMoveThree(move, board);
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


int LevelThree::evaluateMoveThree(const std::pair<Position, Position> &move, Board* board) const {
    int avoidScore = 0;
    Position start = move.first;
    Position end = move.second;
    Piece* movingPiece = board->getState()[start.posX][start.posY];
    Piece* targetPiece = board->getState()[end.posX][end.posY];
    int captureScore = 0;
    int checkScore = 0;
    string oppColour;
    int bestScore = 0;

    // Score for capturing a piece
    if (targetPiece != nullptr && movingPiece != nullptr && board->canCapture(start,end) && targetPiece->getColour() != movingPiece->getColour()) {
        captureScore += targetPiece->getScoreValue();
    }
    
    // Score for avoiding capture
    if (moveAvoidsCapture(move, board, movingPiece->getColour())) {
        avoidScore = movingPiece->getScoreValue();
    }

    if(movingPiece->getColour() == "white") {
        oppColour = "black";
    } else if(movingPiece->getColour() == "black") {
       oppColour = "white"; 
    }


    // Score for checking the opponent's king
    if (board->isInCheckAfterMove(move.first, move.second, oppColour)) {
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

bool LevelThree::moveAvoidsCapture(const std::pair<Position, Position> &move, Board* board, const std::string& playerColour) const {
    Piece* movedPiece = board->getState()[move.first.posX][move.first.posY];
    Piece* copy;
    bool captured = false;
    Piece* dup;
    Position temp = move.second;

    // // Temporarily make the move

    // // checks if there is a piece that exists when trying to move the piece
    if(board->getState()[temp.posX][temp.posY] != nullptr) {
        cout << board->getState()[temp.posX][temp.posY]->displayChar() << endl;
        dup = board->duplicate(board->getState()[temp.posX][temp.posY]);
        captured = true; 
    }

    if(board->getState()[move.first.posX][move.first.posY]->getType() == Piece::KING || 
        board->getState()[move.first.posX][move.first.posY]->getType() == Piece::PAWN || 
        board->getState()[move.first.posX][move.first.posY]->getType() == Piece::ROOK) {
        copy = board->getState()[move.first.posX][move.first.posY];
    }

    board->makeMove(movedPiece, temp);

    // Check if any opponent's piece can capture the moved piece
    bool isSafe = true;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* potentialAttacker = board->getState()[x][y];
            if (potentialAttacker != nullptr && potentialAttacker->getColour() != playerColour) {
               Position attackerPosition = {x, y};
                if (board->canCapture(attackerPosition, temp)) {
                    isSafe = false;
                    break;
                }
            }
        }
        if (!isSafe) break;
    }

    // // Revert the move
    board->undoMove(dup,captured,move.first,temp);
    
    if(copy != nullptr) {
        board->getState()[move.first.posX][move.first.posY] = copy;
    }

    return isSafe;
}

