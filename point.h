#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(int x , int y);
    bool operator == (const Point& p) const;

    void setX(int x);
    void setY(int y);
    int x() const;
    int y() const;
private:
    int m_x;
    int m_y;
};

#endif // POINT_H
