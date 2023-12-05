#ifndef __LEVELFIVE_H__
#define __LEVELFIVE_H__
#include "levelfour.h"
#include <vector>
#include <map>

class LevelFive : public LevelFour {
    mutable std::vector<std::pair<Position, Position>> openingBook;
    mutable bool useOpeningBook;
public:
    LevelFive(const std::string& colour, std::string playerType);
    pair<Position, Position> algorithm(Board* board) const override;
    void loadOpeningBook();
    std::pair<Position, Position> selectOpeningMove(Board* board) const;
    int getComputerLevel() const override { return 5; }
};

#endif // __LEVELFOUR_H__
