#ifndef CHESSMAN_H
#define CHESSMAN_H
#include "point.h"
#include "vector"
#include "rect.h"
#include <algorithm>

class Chessman{

public:
Chessman(const Point& pos );
virtual ~Chessman() = default;
Chessman(const Chessman& chessman) = default;
Chessman& operator= (const Chessman& chessman) = default;
Chessman(Chessman&& chessman) = default;
Chessman& operator = (Chessman&& chessman) = default;


virtual bool move(const Point& point);
const Point& currentPoint() const;
virtual std::vector<Point> possibleMoves() const = 0;
protected:
Point m_currentPoint;
virtual bool movePointIsValid(const Point& point ) const;
};

#endif
