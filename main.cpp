#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "threadpool.h"
#include "chessboard.h"
#include "commander.h"
#include <ctime>
#include <thread>

void saveResult(double time , int possibleSolutions){
  std::ofstream fileOutput("output.txt");
  fileOutput << possibleSolutions;
  fileOutput.close();

  std::ofstream fileTime("time.txt");
  fileTime << time;
  fileTime.close();
}


int main()
{
  std::vector<std::string> lines;
  std::string line;

  std::ifstream file;
  file.open("input.txt");


  if(!file.is_open()) {
      exit(1);
    }

  int nThreads;
  file >> nThreads;

  int sizeChessBoard;
  file >> sizeChessBoard;

  size_t countNeedMakeChessman;
  file >> countNeedMakeChessman;

  int makedChessman;
  file >> makedChessman;

  ThreadPool threadPool(nThreads);

  int xMakedChessman , yMakedChessman;
  std::vector<std::shared_ptr<Chessman>> chessmans;
  std::vector<Point> pointsChessman;

  while (file >> xMakedChessman >> yMakedChessman)
    {
      pointsChessman.emplace_back(xMakedChessman , yMakedChessman);
      chessmans.emplace_back(new Commander(Point(xMakedChessman , yMakedChessman) ));
    }

  file.close();

  double time = clock();

  ChessBoard board(sizeChessBoard , sizeChessBoard);
  board.setChessmans(chessmans);


  std::vector<std::shared_ptr<Chessman>> m_newChessmans;
  m_newChessmans.reserve(countNeedMakeChessman);

  std::vector<Point> occupiedPoints = pointsChessman;

  for(const Point& point : pointsChessman){

      std::vector<Point> points =  board.possibleMoves(point);
      occupiedPoints.insert(occupiedPoints.end() , points.begin() , points.end());
    }



  std::vector<Point> allPoint;
  for(int columnIndex = 0; columnIndex < sizeChessBoard; ++columnIndex) {

      for(int rowIndex = 0; rowIndex < sizeChessBoard; ++rowIndex){

          allPoint.emplace_back( columnIndex , rowIndex );
        }

    }


  auto comparePoint  =  [] (const Point& p1 , const Point& p2  ) {

      if(p1.x() < p2.x()){
          return true;
        }else if (p1.x() == p2.x()) {
          if(p1.y() < p2.y()){
              return true;
            }else{
              return false;
            }

        }else{
          return false;
        }

    };

  std::sort(occupiedPoints.begin() , occupiedPoints.end() , comparePoint);
  auto last = std::unique(occupiedPoints.begin() , occupiedPoints.end());
  occupiedPoints.erase(last ,occupiedPoints.end() );
  std::sort(allPoint.begin() , allPoint.end() , comparePoint);

  std::vector<Point> vacantPoints;
  std::set_difference(allPoint.begin() , allPoint.end() ,
                      occupiedPoints.begin() , occupiedPoints.end(),
                      std::back_inserter(vacantPoints) ,
                      comparePoint );


  if(vacantPoints.size() < countNeedMakeChessman){
      time = clock() -  time;
      saveResult(time, 0);
      return 0;
    }


  std::vector<std::future<bool>> futures;
  std::vector<std::vector<Point>> solutions;
  solutions.reserve(vacantPoints.size());

  pthread_mutex_t mutexSolutionsVector;
  pthread_mutex_init(&mutexSolutionsVector, NULL);

  int counter =0;

  do{

      counter++;
      std::packaged_task<bool()> task([vacantPoints, board , countNeedMakeChessman ,&solutions,&mutexSolutionsVector , counter]() mutable
      {

          pthread_t id = pthread_self();
          std::cout << "Thread id: " << id << " Task num: " << counter <<std::endl;

          std::vector<std::shared_ptr<Chessman>> chessmans;
          for(size_t i = 0; i < countNeedMakeChessman; ++i){
              chessmans.emplace_back(new Commander(vacantPoints[i]));
            }

          board.appendChessmans(chessmans);

          for(const std::shared_ptr<Chessman>& chessman : chessmans){

              std::vector<Point> possibleMoves = chessman->possibleMoves();

              for(const Point& point : possibleMoves){

                  auto it = std::find_if(chessmans.begin() , chessmans.end() , [&point] (const std::shared_ptr<Chessman>& c) {
                      return c->currentPoint() == point;
                    } );

                  if(it!= chessmans.end()){
                      return false;
                    }

                }
            }

          pthread_mutex_lock(&mutexSolutionsVector);
          for(const std::vector<Point>& solution : solutions){
              if(std::is_permutation(solution.begin() , solution.end() , vacantPoints.begin() ) ){
                  pthread_mutex_unlock(&mutexSolutionsVector);
                  return false;
                }
            }
          solutions.emplace_back( std::vector<Point>(vacantPoints.begin() , vacantPoints.begin() + countNeedMakeChessman) );
          pthread_mutex_unlock(&mutexSolutionsVector);

          return true;

        });


      futures.push_back(task.get_future());
      threadPool.putTask(std::move(task));


    }  while(std::next_permutation(vacantPoints.begin() , vacantPoints.end() , comparePoint ) );


  int counterResult = 0;
  while(!futures.empty()){

      if(futures.back().get()){
          counterResult++;
        }

      futures.pop_back();
    }

  threadPool.stop();

  time = clock() -  time;

  saveResult(time,counterResult);

  std::cout << "finished" << std::endl;

  return 0;
}


