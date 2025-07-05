cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
add_executable(RTSGameEngine
        src/main.cpp
        src/main.cpp
        src/main.cpp
        src/main.cpp
)

# Include directories
target_include_directories(RTSGameEngine
        PRIVATE
        RTSGameEngine/include
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
