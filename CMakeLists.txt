cmake_minimum_required(VERSION 3.14)

project(Narcisse)

add_subdirectory(lib)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build: DEBUG or RELEASE" FORCE)
    message(WARNING "Not build type specified. Falling back to DEBUG.")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Werror -O3 -march=native")

set(APP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GL_LIBS "-lglut -lGLEW -lGLU")

# Narcisse viewer
add_executable(viewer)
target_sources(viewer
               PRIVATE ${APP_SOURCE_DIR}/viewer.cc)
target_link_libraries(viewer spdlog::spdlog)
set_target_properties(viewer PROPERTIES CXX_STANDARD 17)


# Narcisse library
add_library(narcisse INTERFACE)
target_sources(narcisse
               INTERFACE ${INCLUDE_DIR}/narcisse/narcisse.hh)
target_include_directories(narcisse INTERFACE ${INCLUDE_DIR})


# Shader compiler
add_executable(compiler)
target_sources(compiler
               PRIVATE ${APP_SOURCE_DIR}/compiler.cc)
set_target_properties(compiler PROPERTIES CXX_STANDARD 17)
target_link_libraries(compiler spdlog::spdlog narcisse ${GL_LIBS} CLI11::CLI11 stdc++fs)
