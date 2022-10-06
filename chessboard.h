#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include <iostream>
#include "chessman.h"
#include <memory>
#include <optional>

class ChessBoard
{
public:

struct PointInfo : public Point{
enum class StatusPoint{
FREE,
ENEMY,
FRIEND
} m_status;
};

public:
ChessBoard( int w , int h );

void putChessmans(std::vector<std::unique_ptr<Chessman> > &&chessmans);
void putChessman(std::unique_ptr<Chessman> chessman);

bool moveChessman(const Point& posChessman , const Point& newPosChessman);
std::vector<std::vector<Chessman::PointWithDirection>> possibleMoves(const Point& posChessman ) const;
bool pointMoveIsPossible(const Point& posChessman , const Point& posMove) const;
bool checkPlaceVacant(const Point& point) const;
bool eraseChessman(const Point& point);
std::vector<Point> currentPointChessmans(const std::vector<std::string>& chessmanNames) const;
int width() const;
int height() const;
private:
std::vector<std::unique_ptr<Chessman>> m_chessmans;
int m_width = 8;
int m_height = 8;
private:
Rect boundingRect() const;
bool pointInChessBoard(const Point& point) const;
};


#endif // CHESSBOARD_H
