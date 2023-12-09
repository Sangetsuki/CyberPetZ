cmake_minimum_required(VERSION 3.13)
project(CyberPetZ)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CyberPetZ src/main.cpp src/monster.cpp src/game.cpp)
target_link_libraries(CyberPetZ ${SDL2_LIBRARIES})
