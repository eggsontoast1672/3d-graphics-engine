cmake_minimum_required(VERSION 3.10)

project(3DGraphicsEngine LANGUAGES C)

find_package(PkgConfig)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(
  engine
  include/engine/renderer/color.h
  include/engine/renderer/renderer.h
  include/engine/engine.h
  include/engine/image.h
  include/engine/mesh.h
  include/engine/shader.h
  include/engine/texture.h
  include/engine/window.h
  src/renderer/color.c
  src/renderer/renderer.c
  src/engine.c
  src/image.c
  src/main.c
  src/mesh.c
  src/shader.c
  src/texture.c
  src/window.c
)

set_property(TARGET engine PROPERTY C_STANDARD 11)
set_property(TARGET engine PROPERTY C_STANDARD_REQUIRED OFF)
set_property(TARGET engine PROPERTY C_EXTENSIONS OFF)

target_include_directories(engine PRIVATE include)
target_link_libraries(engine PRIVATE ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
