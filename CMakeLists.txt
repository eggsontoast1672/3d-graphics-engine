cmake_minimum_required(VERSION 3.10)

project(3DGraphicsEngine LANGUAGES CXX)

find_package(PkgConfig)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(
  engine
  include/engine/renderer/color.hpp
  include/engine/renderer/renderer.hpp
  include/engine/engine.hpp
  include/engine/image.hpp
  include/engine/mesh.hpp
  include/engine/shader.hpp
  include/engine/texture.hpp
  include/engine/window.hpp
  src/renderer/color.cpp
  src/renderer/renderer.cpp
  src/engine.cpp
  src/image.cpp
  src/main.cpp
  src/mesh.cpp
  src/shader.cpp
  src/texture.cpp
  src/window.cpp
)

set_property(TARGET engine PROPERTY CXX_STANDARD 17)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED OFF)
set_property(TARGET engine PROPERTY CXX_EXTENSIONS OFF)

target_include_directories(engine PRIVATE include)
target_link_libraries(engine PRIVATE ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
