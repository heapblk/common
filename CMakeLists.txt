cmake_minimum_required(VERSION 3.28)

project(common)

set(CMAKE_CXX_STANDARD 23)

add_executable(common)
target_sources(common
        PUBLIC
        "src/main.cc"
)

target_sources(common
        PUBLIC
        FILE_SET CXX_MODULES FILES
        "src/modules/flagparser.cppm"
        "src/modules/iparser.cppm"
        "src/modules/fileio.cppm"
        "src/modules/parsers/cxx_parser.cppm"
        "src/modules/parsers/python_parser.cpp"
)
