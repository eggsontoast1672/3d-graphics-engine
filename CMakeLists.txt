cmake_minimum_required(VERSION 3.10)

project(3DGraphicsEngine LANGUAGES CXX)

find_package(PkgConfig)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(engine src/main.cpp)

set_property(TARGET engine PROPERTY CXX_STANDARD 17)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED OFF)
set_property(TARGET engine PROPERTY CXX_EXTENSIONS OFF)

target_link_libraries(engine PRIVATE ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
