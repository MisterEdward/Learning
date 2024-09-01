cmake_minimum_required(VERSION 3.29)
project(Learning)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(edabit)

add_executable(Learning
        edabit/easy/broken_bridge.cpp
        edabit/easy/count_syllables.cpp
        edabit/easy/double_char.cpp
        edabit/easy/last_digit_ultimate.cpp
        edabit/easy/the-cooler-count_syllables.cpp
        edabit/medium/combinations_dar_nu_prea.cpp
        edabit/medium/diagonal_of_cube.cpp
        edabit/medium/tweaking_letters.cpp
        code.cpp
        README.md)
