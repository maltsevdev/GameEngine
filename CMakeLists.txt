cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME GameEngine)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp 
	src/Render/ShaderProgram/ShaderProgram.cpp
	src/Render/ShaderProgram/ShaderProgram.h
	src/Render/VBO/VBO.cpp
	src/Render/VBO/VBO.h
	include/glad/glad.c 
	include/glad/glad.h
	src/glfwCallback/glfwCallback.cpp
	src/glfwCallback/glfwCallback.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)