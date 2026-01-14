cmake_minimum_required(VERSION 3.12)

project(3DGraphicsEngine LANGUAGES CXX)

find_package(PkgConfig)

pkg_check_modules(SDL3 REQUIRED sdl3)

add_executable(
  engine
  include/raspberry/math.hpp
  include/raspberry/renderer.hpp
  include/raspberry/types.hpp
  src/main.cpp
  src/renderer.cpp
)

set_property(TARGET engine PROPERTY CXX_STANDARD 20)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET engine PROPERTY CXX_EXTENSIONS OFF)

target_compile_definitions(engine PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(engine PRIVATE include)
target_link_libraries(engine PRIVATE ${SDL3_LIBRARIES})
