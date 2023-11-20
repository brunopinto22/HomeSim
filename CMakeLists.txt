cmake_minimum_required(VERSION 3.23)
project(HomeSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(HomeSim main.cpp curses.h Terminal.h Terminal.cpp Prompt.cpp Prompt.h)

target_link_libraries(${PROJECT_NAME} C:/Users/HP/Desktop/Bruno/4.Documentos/1.Escola/Uni/2Ano/1Semestre/POO/1.TP/PDCurses-3.9/wincon/pdcurses.a)