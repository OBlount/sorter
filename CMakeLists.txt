cmake_minimum_required(VERSION 3.20)
project(Sorter VERSION 1.0.0 LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
	${PROJECT_NAME}
	src/main.c
)

target_link_libraries(${PROJECT_NAME} SDL2)
