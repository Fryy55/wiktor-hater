cmake_minimum_required(VERSION 3.10)
project(wiktorhater)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

include_directories(C:/Users/User/Documents/D++/include/dpp-10.1)
link_directories(C:/Users/User/Documents/D++/lib/dpp-10.1)

add_executable(wiktorhater src/main.cpp)
set_target_properties(wiktorhater PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin$<0:>)
target_link_libraries(wiktorhater dpp)