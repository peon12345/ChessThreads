#include "king.h"

King::King(const Point &point) : Chessman(point)
{

}

std::vector<std::vector<Chessman::PointWithDirection> > King::possibleMoves() const
{
using Direction = Chessman::PointWithDirection::Direction;

std::vector<std::vector<Chessman::PointWithDirection> > result;
result.reserve(8);

using vec = std::vector<Chessman::PointWithDirection>;

result.emplace_back( vec{ {Point( m_currentPoint.x() - 1 ,m_currentPoint.y() + 1) , Direction::DIAGONAL_UP_LEFT} }); //pointDiagonalUpLeft
result.emplace_back( vec{ {Point( m_currentPoint.x() - 1 ,m_currentPoint.y() - 1) , Direction::DIAGONAL_DOWN_LEFT}} ); //pointDiagonalDownLeft
result.emplace_back( vec{ {Point( m_currentPoint.x() + 1 ,m_currentPoint.y() + 1) , Direction::DIAGONAL_UP_RIGHT}} ); //pointDiagonalUpRight
result.emplace_back( vec{ {Point( m_currentPoint.x() + 1 ,m_currentPoint.y() - 1) , Direction::DIAGONAL_DOWN_RIGHT}} ); //pointDiagonalDownRight
result.emplace_back( vec{ {Point( m_currentPoint.x() ,m_currentPoint.y() + 1) , Direction::UP }}); //pointUp
result.emplace_back( vec{ {Point( m_currentPoint.x() ,m_currentPoint.y() - 1) , Direction::DOWN }}); //pointDown
result.emplace_back( vec{ {Point( m_currentPoint.x()-1 ,m_currentPoint.y()) , Direction::LEFT }}); //pointLeft
result.emplace_back( vec{ {Point( m_currentPoint.x() +1 ,m_currentPoint.y()) , Direction::RIGHT }}); //pointRight

return result;
}

