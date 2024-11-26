cmake_minimum_required(VERSION 3.21)
project(BasicJPEG)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(extern/googletest)
add_subdirectory(test)

file(GLOB BMP_FILES "samples/*.bmp" "samples/*.jpg")
file(COPY ${BMP_FILES} DESTINATION ${CMAKE_BINARY_DIR}/samples)
