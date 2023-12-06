#include "levelone.h"
#include <utility>
#include <random>

using namespace std;

pair<Position, Position> LevelOne::algorithm(Board* board) const {
    // Get available moves from the map
    map<Position, vector<Position>> availableMoves = getAvailableMoves();
    string oppColour;

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
            Piece *movingPiece = board->getState()[randomPosition.posX][randomPosition.posY];

            if(movingPiece->getColour() == "white") {
                oppColour = "black";
            } else if(movingPiece->getColour() == "black") {
            oppColour = "white"; 
            }

            if(movingPiece->getType() == Piece::KING && board->isInCheckAfterMove(randomPosition,randomMove,oppColour)) { 
                continue;
            }
            
            return make_pair(randomPosition, randomMove);
        }
        
    }
}
