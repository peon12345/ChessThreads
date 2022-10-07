#ifndef COMMANDER_H
#define COMMANDER_H
#include "chessman.h"


class Commander : public Chessman
{
public:
    Commander(const Point& point);
    std::vector<Point> possibleMoves() const override;
};

#endif // COMMANDER_H
