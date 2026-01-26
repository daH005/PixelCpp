cmake_minimum_required(VERSION 3.5)

project(PixelCpp)

find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    set(BIN_FOLDER "./SFML-2.6.2/bin/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${BIN_FOLDER}sfml-system-2.dll"
        "${BIN_FOLDER}sfml-window-2.dll"
        "${BIN_FOLDER}sfml-graphics-2.dll"
        "${BIN_FOLDER}sfml-system-d-2.dll"
        "${BIN_FOLDER}sfml-window-d-2.dll"
        "${BIN_FOLDER}sfml-graphics-d-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    "../assets"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)