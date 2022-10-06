#include "rect.h"

//Rect::Rect() : m_height(0) , m_width(0)
//{
// calculateSides();
//}

Rect::Rect(Point leftTop, Point rightBottom) : m_leftTop(leftTop) , m_rightBottom(rightBottom)
{
    calculateSides();
}

int Rect::height() const
{
 return m_height;
}

int Rect::width() const
{
    return m_width;
}

bool Rect::contains(const Point &p) const
{
   return m_leftTop.x() < p.x() && p.x() < m_rightBottom.x() &&
           m_leftTop.y() > p.y() && m_rightBottom.y() < p.y();
}

Point Rect::topRight() const
{
    return m_rightTop;
}

Point Rect::bottomLeft() const
{
    return m_leftBottom;
}

Point Rect::topLeft()
{
    return m_leftTop;
}

Point Rect::rightBottom()
{
    return m_rightBottom;
}

void Rect::calculateSides()
{
    m_leftBottom = Point( m_leftTop.x() , m_rightBottom.x() );
    m_rightTop = Point( m_leftTop.x() + m_rightBottom.x() , m_leftTop.y()  );

    m_height = m_leftTop.y() -  m_rightBottom.y();
    m_width  = m_rightBottom.x() -  m_leftTop.x();

}

