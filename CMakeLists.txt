cmake_minimum_required(VERSION 3.22)
project(Snek C)

set(CMAKE_C_STANDARD 17)

add_executable(Snek main.c)

target_link_libraries(Snek -lmingw32 -lallegro-5.0.10-monolith-md-debug)