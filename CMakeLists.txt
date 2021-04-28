cmake_minimum_required(VERSION 3.12)

project(regression LANGUAGES C)

find_package(Python 3.6)

add_compile_options(-O)
add_subdirectory(src)
add_subdirectory(app)
