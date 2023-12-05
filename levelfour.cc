#include "levelfour.h"
using namespace std;

LevelFour::LevelFour(const string& colour, string playerType) : LevelThree(colour, playerType) {}

pair<Position, Position> LevelFour::algorithm(Board* board) const {
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
         map<Position, vector<Position>> availableMoves = getAvailableMoves();

        // Check if there are any available moves 
        if (availableMoves.empty()) {
            // No available moves, return a default pair (for testing purposes)
            return make_pair(Position{-1, -1}, Position{-1, -1});
        }
        
        // Use a random device to generate a random index for positions
        random_device dev;
        mt19937 gen(dev());
        uniform_int_distribution<size_t> positionDistribution(0, availableMoves.size() - 1);

        while (true) {
            size_t randomPositionIndex = positionDistribution(gen);

            // Use an iterator to find the random element in the map for positions
            auto positionIterator = next(begin(availableMoves), randomPositionIndex);
            Position randomPosition = positionIterator->first;

            // Get the available moves for the randomly selected position
            const vector<Position>& movesForRandomPosition = positionIterator->second;

            // Check if there are any available moves for the selected position
            if (!movesForRandomPosition.empty()) {
                // Use a random index for moves
                uniform_int_distribution<size_t> moveDistribution(0, movesForRandomPosition.size() - 1);
                size_t randomMoveIndex = moveDistribution(gen);

                // Get the random move for the selected position
                Position randomMove = movesForRandomPosition[randomMoveIndex];

                return make_pair(randomPosition, randomMove);
            }
        }
    }


    return bestMove;
}


int LevelFour::evaluateMove(const std::pair<Position, Position> &move, Board* board) const {
    int score = 0;
    Position start = move.first;
    Position end = move.second;
    Piece* movingPiece = board->getState()[start.posX][start.posY];
    Piece* targetPiece = board->getState()[end.posX][end.posY];

    // Score for capturing a piece
    if (targetPiece != nullptr && movingPiece != nullptr && board->canCapture(start,end) && targetPiece->getColour() != movingPiece->getColour()) {
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

bool LevelFour::moveAvoidsCapture(const std::pair<Position, Position> &move, Board* board, const std::string& playerColour) const {
    Piece* movedPiece = board->getState()[move.first.posX][move.first.posY];
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

    return isSafe;
}

