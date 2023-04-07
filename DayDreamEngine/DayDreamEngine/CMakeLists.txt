cmake_minimum_required(VERSION 3.26)

project(DayDreamEngine)

find_package(Vulkan REQUIRED)
find_package(spirv_cross_c_shared REQUIRED)
find_package(glfw3 3.3
    REQUIRED
    HINTS "$ENV{GLFW3_INSTALL_DIR}"
)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

file(GLOB ${PROJECT_NAME}_SOURCES ${PROJECT_SOURCE_DIR}/*.c*)
file(GLOB ${PROJECT_NAME}_LIBRARIES_SOURCES ${PROJECT_SOURCE_DIR}/Libraries/*.c*)

add_executable(
    ${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_LIBRARIES_SOURCES}
)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
        cxx_std_20
)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC
        -std=c++20
        -fms-extensions
        -Xlinker --verbose
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $ENV{GLFW3_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/Libraries/Includes
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        DreamLibrary
        ${Vulkan_LIBRARIES}
        glfw
        GL
        /usr/lib/libspirv-cross-core.a
        /usr/lib/libspirv-cross-c.a
        spirv-cross-c-shared
        /usr/lib/libspirv-cross-util.a
        /usr/lib/libspirv-cross-util.a
        /usr/lib/libspirv-cross-cpp.a
        /usr/lib/libspirv-cross-glsl.a
)