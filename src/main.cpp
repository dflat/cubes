#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM for matrices
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard c++ libs
#include <iostream>
// Game objects

#include "Cube.h"
#include "Shader.h"
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Input.h"

#include "Game.h"

int main()
{
    // Initialize GLFW window
    Window window(800, 600, "Colored Cube");
    if (!window.init()) return -1;

    // Initialize GLAD to load OpenGL function pointers (after window/context creation)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    Game game(window);

    if (!game.init()) return -1;

    game.run();

    glfwTerminate();
    return 0;
}
