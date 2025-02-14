cmake_minimum_required(VERSION 3.10)
project(CubeProject)

set(CMAKE_CXX_STANDARD 17)

# silence deprecation warnings for openGL on macos
add_definitions(-DGL_SILENCE_DEPRECATION)

# Find GLFW package
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)  # Ensure OpenGL is found

# Add glad as a library
add_library(glad "vendor/glad.c")
target_include_directories(glad PUBLIC "include")

# Add a library target for Cube (including Shader)
add_library(CubeLib
    #src/Cube.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Renderer.cpp
    src/Camera.cpp
    src/Input.cpp
    src/Entity.cpp
    src/Mesh.cpp
    src/Light.cpp
    src/Game.cpp
)
target_include_directories(CubeLib PUBLIC "include")
# Add GLM from the vendor directory
target_include_directories(CubeLib PRIVATE ${CMAKE_SOURCE_DIR}/vendor/glm/glm-0.9.9.8)
#target_link_libraries(CubeLib PRIVATE glad glfw OpenGL::GL)
target_link_libraries(CubeLib PUBLIC glad glfw OpenGL::GL)

# Add the main executable
add_executable(game src/main.cpp)

# Link all necessary libraries
target_link_libraries(game PRIVATE CubeLib)# glfw)
