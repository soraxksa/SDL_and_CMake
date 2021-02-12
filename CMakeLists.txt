cmake_minimum_required(VERSION 3.10)
project(SDL_CMake)

set(LINK_LIBS SDL2 SDL2_image)

include_directories(include)

file(GLOB SOURCES "src/*.cc")

add_executable(main ${SOURCES})
target_link_libraries(main ${LINK_LIBS})
