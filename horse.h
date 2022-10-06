#ifndef HORSE_H
#define HORSE_H

#include "chessman.h"

class Horse : public Chessman
{
public:
Horse(const Point& point);
~Horse() override = default;
Horse(const Horse& horse) = default;
Horse& operator= (const Horse& horse) = default;
Horse(Horse&& horse) = default;
Horse& operator = (Horse&& horse) = default;

std::vector<std::vector<PointWithDirection>> possibleMoves() const override;
};

#endif // HORSE_H
