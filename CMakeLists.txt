cmake_minimum_required(VERSION 3.13)
project(TamagotchiZ)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(TamagotchiZ src/main.cpp src/monster.cpp)
target_link_libraries(TamagotchiZ ${SDL2_LIBRARIES})
