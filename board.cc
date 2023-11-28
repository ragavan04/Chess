#include "board.h"
using namespace std;

Board::Board() : grid{8, vector<Piece*>(8,nullptr)}, turn{0}, isWin{false}, views{vector<View*>(2,nullptr)} {}








