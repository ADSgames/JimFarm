cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

project (JimFarm)

find_library(ALLEGRO_LIBRARY NAMES liballeg44.dll.a liballeg44.so liballeg.4.4.dylib)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable (JimFarm ${SOURCES} ${HEADERS})

target_compile_options(JimFarm PRIVATE -Wall -Wextra -pedantic)

target_link_libraries(JimFarm ${ALLEGRO_LIBRARY})