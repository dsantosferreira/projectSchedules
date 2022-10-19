cmake_minimum_required(VERSION 3.23)
project(Projeto_schedule)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_schedule main.cpp Classes/Student.cpp Classes/Student.h Classes/UcClass.cpp Classes/UcClass.h Classes/Lecture.cpp Classes/Lecture.h Classes/dataBase.cpp Classes/dataBase.h)
