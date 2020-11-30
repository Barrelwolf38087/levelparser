cmake_minimum_required(VERSION 3.17)
project(levelparser)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC src/levelparser.cpp include/levelparser.hpp)

target_include_directories(${PROJECT_NAME}
        INTERFACE ${PROJECT_SOURCE_DIR}/include
        )

if (LP_BUILD_TEST)
    add_subdirectory(test)
endif()