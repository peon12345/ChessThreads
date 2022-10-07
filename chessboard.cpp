#include "chessboard.h"

ChessBoard::ChessBoard(int w, int h) : m_width(w) , m_height(h)
{
  m_chessmans.reserve(w*h);
}

void ChessBoard::setChessmans(const std::vector<std::shared_ptr<Chessman>>& chessmans)
{
  m_chessmans = chessmans;
}

void ChessBoard::appendChessmans(const std::vector<std::shared_ptr<Chessman> >& chessmans)
{
  //проверка на занятое место

  // for(const std::shared_ptr<Chessman>& newChessman : chessmans){
  //  if(  std::any_of(m_chessmans.begin() , m_chessmans.end() , [&newChessman](const std::shared_ptr<Chessman>& chessman) {

  //        return chessman->currentPoint() == newChessman->currentPoint();

  //      }))
  //    {
  //      return false;
  //    }
  //   }

  m_chessmans.insert(m_chessmans.end() , chessmans.begin(), chessmans.end());
}

bool ChessBoard::moveChessman(const Point &posChessman, const Point &newPosChessman)
{
  auto itChess = std::find_if(m_chessmans.begin() , m_chessmans.end() , [posChessman] ( const std::shared_ptr<Chessman>& chessman) {

      return posChessman == chessman.get()->currentPoint(); } );


  if(itChess == m_chessmans.end()){

      return false;
    }

  if(!pointInChessBoard(newPosChessman)){
      return false;
    }

  if(!itChess->get()->move(newPosChessman)){
      return false;
    }

  return true;
}

std::vector<Point> ChessBoard::possibleMoves(const Point& posChessman) const
{
  std::vector<Point> result;

  auto itSelectedChessman = std::find_if(m_chessmans.begin() , m_chessmans.end() , [posChessman] (const std::shared_ptr<Chessman>& chessman) {
      return posChessman == chessman.get()->currentPoint();
    });

  if(itSelectedChessman == m_chessmans.end() ) {
      return result;
    }

  result = itSelectedChessman->get()->possibleMoves();

  for( auto itPoint = result.begin(); itPoint != result.end(); ) {

      if(!pointInChessBoard(*itPoint)){

          itPoint =  result.erase(itPoint);
          continue;;

        }

      if( checkPlaceVacant(*itPoint)){

          itPoint =   result.erase(itPoint);
          break;

        }

      ++itPoint;
    }

  return result;
}

bool ChessBoard::pointMoveIsPossible(const Point &posChessman, const Point &posMove) const
{
  std::vector<Point> possiblePoints = possibleMoves(posChessman);

  auto it( std::find_if(possiblePoints.begin() , possiblePoints.end() , [&posMove](const Point& p) { return posMove == p; } ));


  return it != possiblePoints.end();

}

bool ChessBoard::checkPlaceVacant(const Point &point) const
{
  auto it( std::find_if( m_chessmans.begin() , m_chessmans.end() , [point] (const std::shared_ptr<Chessman>& chessman) {
      return chessman.get()->currentPoint() == point; }));

  return   it != m_chessmans.end();
}

bool ChessBoard::eraseChessman(const Point &point)
{

  auto it = std::find_if (m_chessmans.begin() , m_chessmans.end() , [&point] (const std::shared_ptr<Chessman>& chessman)
  { return chessman.get()->currentPoint() == point;} );


  if( it != m_chessmans.end() ) {

      m_chessmans.erase(it);
      return true;
    }else{
      return false;
    }
}


int ChessBoard::width() const
{
  return m_width;
}

int ChessBoard::height() const
{
  return m_height;
}


Rect ChessBoard::boundingRect() const
{
  return Rect(Point(0 , m_height-1) , Point (m_width-1 , 0) ) ;
}

bool ChessBoard::pointInChessBoard(const Point &point) const
{
  return boundingRect().contains(point);
}
