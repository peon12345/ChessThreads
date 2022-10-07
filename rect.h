#ifndef RECT_H
#define RECT_H
#include "point.h"

class Rect
{
public:
  Rect( Point leftTop , Point rightBottom );
  int height() const;
  int width() const;
  bool contains(const Point& p) const;
  Point topRight() const;
  Point bottomLeft() const;
  Point topLeft();
  Point rightBottom();
private:
  int m_height;
  int m_width;
  Point m_leftTop;
  Point m_rightBottom;
  Point m_rightTop;
  Point m_leftBottom;
private:
  void calculateSides();
};

#endif // RECT_H
