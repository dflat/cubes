#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Input.h"

class Game {
public:
    // Constructor
    Game(Window& win);

    bool init();

    // Run the main game loop
    void run();

private:
    // Process input (keyboard, mouse, etc.)
    void processInput();

    // Update game state (e.g., camera, objects)
    void update(float t, float dt);

    // Render the scene
    void render();

    // Member variables
    Window& window;
    Renderer renderer;
    Shader shader;
    Cube cube;
    Camera camera;
    glm::mat4 model;
    glm::vec3 lightPos;
};

#endif // GAME_H