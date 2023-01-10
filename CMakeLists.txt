cmake_minimum_required(VERSION 3.0.0)
project(aoc-2022 VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB all_SRCS 
    "main.cpp" 
    "solvers/*.cpp"
    "utils/*.cpp"
    )

add_executable(aoc-2022 ${all_SRCS})

target_compile_features(aoc-2022 PRIVATE cxx_std_20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
