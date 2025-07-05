cmake_minimum_required(VERSION 3.10)
project(RTSGameEngine)

set(CMAKE_CXX_STANDARD 17)

# Ищем OpenGL и GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# GLFW как сабмодуль или пакет
find_package(glfw3 REQUIRED)

# Добавляем исполняемый файл
add_executable(RTSGameEngine
    src/main.cpp
    src/glad.c
)

# Папка include с GLAD и GLFW
target_include_directories(RTSGameEngine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Линкуем библиотеки
target_link_libraries(RTSGameEngine
    glfw
    OpenGL::GL
    GLUT::GLUT
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
