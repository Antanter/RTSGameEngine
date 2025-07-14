cmake_minimum_required(VERSION 3.10)
project(RTSGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

add_executable(RTSGameEngine
    src/main.cpp
)

include_directories(/usr/include/freetype2)

set(CMAKE_TOOLCHAIN_FILE "C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake")

target_include_directories(RTSGameEngine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(RTSGameEngine
    glfw
    OpenGL::GL
    GLUT::GLUT
    Freetype::Freetype
)

# OS-specific settings
if(WIN32)
    message(STATUS "Configuring for Windows")
    target_compile_definitions(RTSGameEngine PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    message(STATUS "Configuring for macOS")
    target_compile_definitions(RTSGameEngine PRIVATE PLATFORM_MACOS)
elseif(UNIX)
    message(STATUS "Configuring for Linux")
    target_compile_definitions(RTSGameEngine PRIVATE PLATFORM_LINUX)
endif()
