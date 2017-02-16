cmake_minimum_required (VERSION 3.3.1 FATAL_ERROR)

project (SquareOne)

# Set cmake folder
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/devops/cmake)
set (CMAKE_PREFIX_PATH $ENV{QT_DIR})

# project macros
include (square-Config)

Config()

add_subdirectory (source)