#include "point.h"

Point::Point() : m_x(0), m_y(0)
{

}

Point::Point(int x, int y) : m_x(x) , m_y(y)
{

}

bool Point::operator ==(const Point &p) const
{
 return p.m_x == m_x && p.m_y == m_y;
}

void Point::setX(int x)
{
    m_x = x;
}

void Point::setY(int y)
{
    m_y = y;
}

int Point::x() const
{
 return m_x;
}

int Point::y() const
{
 return m_y;
}
