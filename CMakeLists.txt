cmake_minimum_required(VERSION 3.13)
project(CyberPetZ)

include_directories(include)

add_executable(CyberPetZ src/main.cpp src/monster.cpp src/game.cpp)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

find_package(SDL2_image REQUIRED)
target_link_libraries(CyberPetZ SDL2_image)
