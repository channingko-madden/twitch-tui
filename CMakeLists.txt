cmake_minimum_required(VERSION 3.10)

project(twitch-tui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ftxui CONFIG REQUIRED)

add_executable(twitch-tui src/main.cpp
src/chat_buffer.cpp)

target_link_libraries(twitch-tui
  PRIVATE ftxui::dom
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
)
