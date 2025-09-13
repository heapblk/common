cmake_minimum_required(VERSION 3.28)

project(comc)

set(CMAKE_CXX_STANDARD 20)
set(CXX clang++)

add_executable(common)
target_sources(common
    PUBLIC
    "src/main.cc"
)

target_sources(common
  PUBLIC
     FILE_SET CXX_MODULES FILES
        "src/modules/parser.cppm"
)
