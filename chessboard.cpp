#include "chessboard.h"

ChessBoard::ChessBoard(int w, int h) : m_width(w) , m_height(h)
{

}

void ChessBoard::putChessmans(std::vector<std::unique_ptr<Chessman>> &&chessmans)
{
    m_chessmans = std::move(chessmans);
}

void ChessBoard::putChessman(std::unique_ptr<Chessman> chessman)
{
    m_chessmans.push_back(std::move(chessman));
}

bool ChessBoard::moveChessman(const Point &posChessman, const Point &newPosChessman)
{
    auto itChess = std::find_if(m_chessmans.begin() , m_chessmans.end() , [posChessman] ( const std::unique_ptr<Chessman>& chessman) {

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

std::vector<std::vector<Chessman::PointWithDirection>> ChessBoard::possibleMoves(const Point& posChessman) const
{
    std::vector<std::vector<Chessman::PointWithDirection>> result;

    auto itSelectedChessman = std::find_if(m_chessmans.begin() , m_chessmans.end() , [posChessman] (const std::unique_ptr<Chessman>& chessman) {
        return posChessman == chessman.get()->currentPoint();
    });

    if(itSelectedChessman == m_chessmans.end() ) {
        return result;
    }

    result = itSelectedChessman->get()->possibleMoves();


    for( std::vector<Chessman::PointWithDirection>& pointsInDirection : result) {

        for( auto itPoint = pointsInDirection.begin(); itPoint != pointsInDirection.end(); ) {

            if(!pointInChessBoard(*itPoint)){

                if(itPoint->direction() == Chessman::PointWithDirection::Direction::NONE) {
                    itPoint = pointsInDirection.erase(itPoint);
                    continue;
                }else{
                    pointsInDirection.erase(itPoint ,pointsInDirection.end() );
                    break;
                }
            }

                if( checkPlaceVacant(*itPoint)){

                    pointsInDirection.erase(itPoint + 1 , pointsInDirection.end());
                    break;

                }

            ++itPoint;
        }
    }

    return result;
}

bool ChessBoard::pointMoveIsPossible(const Point &posChessman, const Point &posMove) const
{
    std::vector<std::vector<Chessman::PointWithDirection>> possiblePoints = possibleMoves(posChessman);

    bool isLegalMove = false;

    for(const std::vector<Chessman::PointWithDirection>& points : possiblePoints ){
        if(auto it( std::find_if(points.begin() , points.end() , [&posMove](const Chessman::PointWithDirection& point) { return posMove == point; } ) ) ;
                it !=points.end() ){

            isLegalMove = true;
            break;
        }

    }

    return isLegalMove;
}

bool ChessBoard::checkPlaceVacant(const Point &point) const
{
    auto it( std::find_if( m_chessmans.begin() , m_chessmans.end() , [point] (const std::unique_ptr<Chessman>& chessman) {
                              return chessman.get()->currentPoint() == point; }));

         return   it != m_chessmans.end();
}

bool ChessBoard::eraseChessman(const Point &point)
{
    if(auto it = std::find_if (m_chessmans.begin() , m_chessmans.end() , [&point] (const std::unique_ptr<Chessman>& chessman)
    { return chessman.get()->currentPoint() == point;} );
            it != m_chessmans.end() ) {

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
    return Rect(Point(0 , m_height) , Point (m_width , 0) ) ;
}

bool ChessBoard::pointInChessBoard(const Point &point) const
{
    return boundingRect().contains(point);
}
