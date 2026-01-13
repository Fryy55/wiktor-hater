cmake_minimum_required(VERSION 3.10)
project(WiktorHater)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${SRC_DIR}/data
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin$<0:>)
target_link_libraries(${PROJECT_NAME} dpp)

include("cmake/CPM.cmake")
CPMAddPackage("gh:Fryy55/bismuth@1.1.0")
target_link_libraries(${PROJECT_NAME} bismuth)