#ifndef CHESSMAN_H
#define CHESSMAN_H
#include "point.h"
#include "vector"
#include "rect.h"
#include <algorithm>

class Chessman{

public:
struct PointWithDirection : public Point{

enum class Direction{
UP,
DOWN,
LEFT,
RIGHT,
DIAGONAL_UP_RIGHT,
DIAGONAL_DOWN_RIGHT,
DIAGONAL_UP_LEFT,
DIAGONAL_DOWN_LEFT,
NONE
};

PointWithDirection(const Point& point , Direction direction);

Direction direction() const;

private:
Direction m_direction;
};

Chessman(const Point& pos );
virtual ~Chessman() = default;
Chessman(const Chessman& chessman) = default;
Chessman& operator= (const Chessman& chessman) = default;
Chessman(Chessman&& chessman) = default;
Chessman& operator = (Chessman&& chessman) = default;




virtual bool move(const Point& point);
const Point& currentPoint() const;
virtual std::vector<std::vector<PointWithDirection>> possibleMoves() const = 0;
protected:
Point m_currentPoint;
virtual bool movePointIsValid(const Point& point ) const;
};

#endif
