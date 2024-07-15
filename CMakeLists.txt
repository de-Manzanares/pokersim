cmake_minimum_required(VERSION 3.28)
project(pokersim)

set(CMAKE_CXX_STANDARD 23)

add_executable(pokersim src/main.cpp
        src/Card.hpp
        src/Deck.hpp
        src/Player.hpp
        src/Table.hpp)
