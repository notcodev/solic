cmake_minimum_required(VERSION 3.10)
project(solic C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} "src/main.c")

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    "-framework IOKit"
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework CoreVideo"
    "-framework CoreFoundation"
)

# Set include directories for your target specifically
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
