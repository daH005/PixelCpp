cmake_minimum_required(VERSION 3.5)

project(PixelCpp)

find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(PixelCpp main.cpp)

set_target_properties(
    PixelCpp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "../"
)

target_link_libraries(PixelCpp PRIVATE sfml-graphics sfml-window sfml-system)

