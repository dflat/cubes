cmake_minimum_required(VERSION 3.14)
project(CubeProject VERSION 0.1.0
                   DESCRIPTION "3D Cube Rendering Project"
                   LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Silence OpenGL deprecation warnings on macOS
if(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

# Export compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Dependencies via FetchContent
# ------------------------------------------------------------------------------
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8  # Updated to latest stable release
    GIT_SHALLOW TRUE  # Only fetch the specified commit
)
# Configure GLFW options - disable unnecessary parts
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM handling - check for local copy first, fetch if not available
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm-0.9.9.8/glm/glm.hpp")
    # Use the local GLM
    set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm-0.9.9.8")
    message(STATUS "Using local GLM in vendor directory")
else()
    # Fetch GLM from GitHub
    message(STATUS "Local GLM not found, fetching from GitHub")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glm)
    set(GLM_INCLUDE_DIR "${glm_SOURCE_DIR}")
endif()

# ------------------------------------------------------------------------------
# Find OpenGL
# ------------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# ------------------------------------------------------------------------------
# Add glad as a library
# ------------------------------------------------------------------------------
add_library(glad "vendor/glad.c")
target_include_directories(glad PUBLIC "include")

# ------------------------------------------------------------------------------
# Set common compiler warnings
# ------------------------------------------------------------------------------
function(set_project_warnings target)
    set(MSVC_WARNINGS
        /W4     # Baseline reasonable warnings
        /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
        /w14254 # 'operator': conversion from 'type1' to 'type2', possible loss of data
        /w14263 # 'function': member function does not override any base class virtual member function
        /w14265 # 'classname': class has virtual functions, but destructor is not virtual
        /w14287 # 'operator': unsigned/negative constant mismatch
        /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
        /w14296 # 'operator': expression is always 'boolean_value'
        /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
        /w14545 # expression before comma evaluates to a function which is missing an argument list
        /w14546 # function call before comma missing argument list
        /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
        /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
        /w14555 # expression has no effect; expected expression with side-effect
        /w14619 # pragma warning: there is no warning number 'number'
        /w14640 # Enable warning on thread un-safe static member initialization
        /w14826 # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
        /w14905 # wide string literal cast to 'LPSTR'
        /w14906 # string literal cast to 'LPWSTR'
        /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
    )
    
    set(CLANG_GCC_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wdouble-promotion
        -Wformat=2
    )
    
    if(MSVC)
        target_compile_options(${target} PRIVATE ${MSVC_WARNINGS})
    else()
        target_compile_options(${target} PRIVATE ${CLANG_GCC_WARNINGS})
    endif()
endfunction()

# ------------------------------------------------------------------------------
# Create GLM interface library to handle includes
# ------------------------------------------------------------------------------
add_library(glm_headers INTERFACE)
target_include_directories(glm_headers INTERFACE ${GLM_INCLUDE_DIR})

# ------------------------------------------------------------------------------
# Create CubeLib library
# ------------------------------------------------------------------------------
add_library(CubeLib
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

# Apply warning settings
#set_project_warnings(CubeLib)

# Set include directories
target_include_directories(CubeLib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies
target_link_libraries(CubeLib
    PUBLIC 
        glad
        glfw
        OpenGL::GL
        glm_headers
)

# ------------------------------------------------------------------------------
# Add the main executable
# ------------------------------------------------------------------------------
add_executable(game src/main.cpp)
target_link_libraries(game PRIVATE CubeLib)

# ------------------------------------------------------------------------------
# Installation rules
# ------------------------------------------------------------------------------
install(TARGETS game
    RUNTIME DESTINATION bin
)

# Copy shader files to build directory
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:game>/shaders
    COMMENT "Copying shaders to build directory"
)

# Copy asset files to build directory
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game>/assets
    COMMENT "Copying assets to build directory"
)
