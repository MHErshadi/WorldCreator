cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenGL REQUIRED)
project(WorldCreator VERSION 0.1.0
    DESCRIPTION "World Creator version 0.1.0"
    LANGUAGES C)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
elseif (MSVC)
    set(CMAKE_C_FLAGS "/Wall /wd4820 /wd4710 /wd5045 /wd4100 /WX")
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/O2 /Zi")
endif()

add_executable(WorldCreator
    srcs/main.c)

target_include_directories(WorldCreator PRIVATE heads)
target_link_directories(WorldCreator PRIVATE libs)
target_link_libraries(WorldCreator PRIVATE OpenGL32 PRIVATE glfw3)