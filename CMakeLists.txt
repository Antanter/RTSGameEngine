cmake_minimum_required(VERSION 3.10)
project(RTSGameEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

add_executable(RTSGameEngine
    src/main.cpp
        src/Rendering/renderable.h
        src/Rendering/label.h
        src/Rendering/text.cpp
)

# Can be deleted
include_directories(/usr/include/freetype2)

target_include_directories(RTSGameEngine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include # Can be deleted ??
)

target_link_libraries(RTSGameEngine
    PRIVATE
    glfw
    OpenGL::GL
    GLUT::GLUT
    glm::glm
    Freetype::Freetype
)

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
