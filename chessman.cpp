#include "chessman.h"

Chessman::Chessman(const Point &pos) : m_currentPoint(pos)
{

}

bool Chessman::move(const Point &point)
{
if(movePointIsValid(point)){
m_currentPoint = point;
return true;
}else{
return false;
}
}


const Point &Chessman::currentPoint() const
{

return m_currentPoint;

}

bool Chessman::movePointIsValid(const Point &point) const
{

//Rect boundingRect( Point(0 , point.y()) , Point(point.x() , 0) );

std::vector<std::vector<PointWithDirection>> points = possibleMoves();

for(const std::vector<PointWithDirection>& pointsInDirection : points ) {

auto itFindPoint = std::find_if(pointsInDirection.begin() , pointsInDirection.end() , [&point] (const PointWithDirection& p) {
 return p.x() == point.x() && p.y() == point.y();
} );

if(itFindPoint != pointsInDirection.end() ) {
return true;
}

}

return false;
}


Chessman::PointWithDirection::PointWithDirection(const Point &point, Direction direction): Point(point) , m_direction(direction)
{

}

Chessman::PointWithDirection::Direction Chessman::PointWithDirection::direction() const
{
return m_direction;
}
