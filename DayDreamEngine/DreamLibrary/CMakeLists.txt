cmake_minimum_required(VERSION 3.26)

project(DreamLibrary)

file(GLOB ${PROJECT_NAME}_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADER_SOURCES ${PROJECT_SOURCE_DIR}/*.h)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADER_SOURCES}
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC
        cxx_std_20
)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20 -fms-extensions)

# if (${PROJECT_NAME}_WARNINGS)
#     target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
# endif()

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/Header
        ${PROJECT_SOURCE_DIR}/../Platform/Universal/Includes
)