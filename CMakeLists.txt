cmake_minimum_required(VERSION 3.5)

project(chessMultiThread LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chessMultiThread  main.cpp
 commander.h commander.cpp 
chessman.h chessman.cpp 
point.h point.cpp 
rect.h rect.cpp
 horse.h horse.cpp 
king.h king.cpp
chessboard.h chessboard.cpp)

