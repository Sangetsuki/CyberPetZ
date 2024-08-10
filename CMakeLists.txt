cmake_minimum_required(VERSION 3.13)
project(CyberPetZ)

include_directories(include)

add_executable(${PROJECT_NAME}
  src/main.cpp src/monster.cpp src/game.cpp src/save.cpp
  src/scene.cpp src/main_menu.cpp src/title_screen.cpp src/sprite.cpp src/rpg.cpp
  src/pong.cpp
  src/gui/button.cpp src/gui/progressbar.cpp src/gui/textbox.cpp
)

find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)
