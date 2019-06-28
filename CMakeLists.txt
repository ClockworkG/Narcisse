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
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(GL_LIBS "-lGL -lglut -lGLEW -lGLU")

# Narcisse viewer
add_executable(viewer)
target_sources(viewer
               PRIVATE ${APP_SOURCE_DIR}/viewer.cc)
target_link_libraries(viewer spdlog::spdlog pogl)
set_target_properties(viewer PROPERTIES CXX_STANDARD 17)


# Narcisse library
add_library(pogl STATIC)
target_sources(pogl
               INTERFACE ${INCLUDE_DIR}/pogl/pogl.hh
               PRIVATE ${SOURCE_DIR}/pogl/program.cc
                       ${SOURCE_DIR}/pogl/context.cc
                       ${SOURCE_DIR}/pogl/scene.cc
                       ${SOURCE_DIR}/pogl/engine.cc
                       ${SOURCE_DIR}/pogl/render-target.cc
                       ${SOURCE_DIR}/pogl/render-buffer.cc
                       ${SOURCE_DIR}/pogl/reflecting.cc
                       ${SOURCE_DIR}/pogl/mesh.cc
                       ${SOURCE_DIR}/pogl/texture.cc
                       ${SOURCE_DIR}/pogl/vertex-attrib-pointer.cc
                       ${SOURCE_DIR}/pogl/camera.cc
                       ${SOURCE_DIR}/pogl/object.cc
                       ${SOURCE_DIR}/pogl/detail/shader-source.cc)
target_include_directories(pogl PUBLIC ${INCLUDE_DIR})
target_link_libraries(pogl ${GL_LIBS} stdc++fs nlohmann_json tinyobjloader)
set_target_properties(pogl PROPERTIES CXX_STANDARD 17)


# Shader compiler
add_executable(compiler)
target_sources(compiler
               PRIVATE ${APP_SOURCE_DIR}/compiler.cc)
set_target_properties(compiler PROPERTIES CXX_STANDARD 17)
target_link_libraries(compiler spdlog::spdlog pogl ${GL_LIBS} CLI11::CLI11 stdc++fs)
