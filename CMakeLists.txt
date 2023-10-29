cmake_minimum_required(VERSION 3.12)

project(ImageProcessingLibrary)

add_subdirectory(MatrixModule)

add_library(${PROJECT_NAME} STATIC Image.cpp Utils.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC MatrixModule)

target_link_libraries(${PROJECT_NAME} PUBLIC MatrixModule)
