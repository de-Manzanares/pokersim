cmake_minimum_required(VERSION 3.28)
project(pokersim)

set(CMAKE_CXX_STANDARD 23)

add_executable(pokersim src/main.cpp
        src/Card.cpp
        src/Deck.cpp
        src/Player.cpp
        src/Table.cpp)
target_include_directories(pokersim PRIVATE ./include)
