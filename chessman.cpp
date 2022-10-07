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

  std::vector<Point> points = possibleMoves();


  auto itFindPoint = std::find_if(points.begin() , points.end() , [&point] (const Point& p) {
      return p.x() == point.x() && p.y() == point.y();
    } );

  if(itFindPoint != points.end() ) {
      return true;
    }



  return false;
}


