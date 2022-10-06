#include "horse.h"


Horse::Horse(const Point& point) : Chessman(point)
{

}

std::vector<std::vector<Chessman::PointWithDirection>> Horse::possibleMoves() const
{

Point topLeft = m_currentPoint;
topLeft.setX(topLeft.x() - 2);
topLeft.setY(topLeft.y() + 2);

Point bottomRight = m_currentPoint;
bottomRight.setX(bottomRight.x() + 2);
bottomRight.setY(bottomRight.y() - 2);

Rect boundingRectHorseMove(topLeft,bottomRight);

Point topRight = boundingRectHorseMove.topRight();
Point bottomLeft = boundingRectHorseMove.bottomLeft();

std::vector<Chessman::PointWithDirection> possiblePoints;
possiblePoints.reserve(8);


using Direction = Chessman::PointWithDirection::Direction;

possiblePoints.emplace_back(Point(topLeft.x() + 1 ,topLeft.y()) , Direction::NONE);
possiblePoints.emplace_back(Point(topRight.x() - 1 ,topRight.y() ) , Direction::NONE);
possiblePoints.emplace_back(Point(topRight.x() ,topRight.y() - 1 ), Direction::NONE);
possiblePoints.emplace_back(Point(bottomRight.x() ,bottomRight.y() + 1 ), Direction::NONE);
possiblePoints.emplace_back(Point(bottomRight.x() - 1 ,bottomRight.y() ), Direction::NONE);
possiblePoints.emplace_back(Point(bottomLeft.x() + 1 ,bottomLeft.y() ), Direction::NONE);
possiblePoints.emplace_back(Point(bottomLeft.x() ,bottomLeft.y() + 1 ), Direction::NONE);
possiblePoints.emplace_back(Point(topLeft.x() ,topLeft.y() - 1 ), Direction::NONE);

std::vector<std::vector<Chessman::PointWithDirection>> result;
result.push_back(possiblePoints);

return result;
}

