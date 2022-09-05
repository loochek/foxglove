cmake_minimum_required(VERSION 3.1)

project(foxglove)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFXG_DEBUG=1 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(glfw3 REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(foxglove)
add_subdirectory(testapp)
add_subdirectory(model_importer)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/stb)
add_subdirectory(thirdparty/json)
