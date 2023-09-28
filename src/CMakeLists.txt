cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(child child_process.c)
add_executable(lab1 lab1.c)
