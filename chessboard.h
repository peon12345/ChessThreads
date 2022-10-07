#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include <iostream>
#include "chessman.h"
#include <memory>
#include <optional>

class ChessBoard
{

public:
ChessBoard( int w , int h );

void setChessmans(const std::vector<std::shared_ptr<Chessman> > &chessmans);
void appendChessmans(const std::vector<std::shared_ptr<Chessman> > &chessmans);

bool moveChessman(const Point& posChessman , const Point& newPosChessman);
std::vector<Point> possibleMoves(const Point& posChessman ) const;
bool pointMoveIsPossible(const Point& posChessman , const Point& posMove) const;
bool checkPlaceVacant(const Point& point) const;
bool eraseChessman(const Point& point);
int width() const;
int height() const;
private:
std::vector<std::shared_ptr<Chessman>> m_chessmans;
int m_width;
int m_height;
private:
Rect boundingRect() const;
bool pointInChessBoard(const Point& point) const;
};


#endif // CHESSBOARD_H
