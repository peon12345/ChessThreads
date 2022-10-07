#include "commander.h"


Commander::Commander(const Point &point) : Chessman(point)
{

}

std::vector<Point> Commander::possibleMoves() const
{

  std::vector<Point> result;
  result.reserve(8);

  result.emplace_back(  m_currentPoint.x() - 1 ,m_currentPoint.y() + 1); //pointDiagonalUpLeft
  result.emplace_back(  m_currentPoint.x() - 1 ,m_currentPoint.y() - 1); //pointDiagonalDownLeft
  result.emplace_back( m_currentPoint.x() + 1 ,m_currentPoint.y() + 1); //pointDiagonalUpRight
  result.emplace_back(m_currentPoint.x() + 1 ,m_currentPoint.y() - 1); //pointDiagonalDownRight
  result.emplace_back(m_currentPoint.x() ,m_currentPoint.y() + 1); //pointUp
  result.emplace_back( m_currentPoint.x() ,m_currentPoint.y() - 1); //pointDown
  result.emplace_back(m_currentPoint.x()-1 ,m_currentPoint.y()); //pointLeft
  result.emplace_back( m_currentPoint.x() +1 ,m_currentPoint.y()); //pointRight


  Point topLeft = m_currentPoint;
  topLeft.setX(topLeft.x() - 2);
  topLeft.setY(topLeft.y() + 2);

  Point bottomRight = m_currentPoint;
  bottomRight.setX(bottomRight.x() + 2);
  bottomRight.setY(bottomRight.y() - 2);

  Rect boundingRectHorseMove(topLeft,bottomRight);

  Point topRight = boundingRectHorseMove.topRight();
  Point bottomLeft = boundingRectHorseMove.bottomLeft();

  result.emplace_back(topLeft.x() + 1 ,topLeft.y());
  result.emplace_back(topRight.x() - 1 ,topRight.y() );
  result.emplace_back(topRight.x() ,topRight.y() - 1 );
  result.emplace_back(bottomRight.x() ,bottomRight.y() + 1 );
  result.emplace_back(bottomRight.x() - 1 ,bottomRight.y());
  result.emplace_back(bottomLeft.x() + 1 ,bottomLeft.y());
  result.emplace_back(bottomLeft.x() ,bottomLeft.y() + 1);
  result.emplace_back(topLeft.x() ,topLeft.y() - 1);

  return result;
}
