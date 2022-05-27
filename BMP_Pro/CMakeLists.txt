cmake_minimum_required(VERSION 3.5)

project(BMP_Pro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_LIST main.cpp image.cpp  )
set(HEAD_LIST image.h  )
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEAD_LIST})
target_link_libraries(BMP_Pro ${CURSES_LIBRARIES})

