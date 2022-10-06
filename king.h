#ifndef KING_H
#define KING_H

#include "chessman.h"

class King : public Chessman
{
public:
King(const Point& point);
~King() override = default;
King(const King& king) = default;
King& operator= (const King& king) = default;
King(King&& king) = default;
King& operator = (King&& king) = default;

std::vector<std::vector<PointWithDirection> > possibleMoves() const override;
};

#endif // KING_H
