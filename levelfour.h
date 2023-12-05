#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__
#include "levelthree.h"
#include <vector>
#include <map>

class LevelFour : public LevelThree {
    mutable std::vector<std::pair<Position, Position>> openingBook;
    mutable bool useOpeningBook;
public:
    LevelFour(const std::string& colour, std::string playerType);
    std::pair<Position, Position> algorithm(Board* board) const override;
    void loadOpeningBook();
    std::pair<Position, Position> selectOpeningMove(Board* board) const;
    int getComputerLevel() const override { return 4; }
};

#endif // __LEVELFOUR_H__
