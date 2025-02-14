#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
//#include "Cube.h"
#include "Mesh.h"
#include "Light.h"
#include "Entity.h"

class Game {
public:
    Game(Window& win);
    ~Game();

    bool init();
    void run();
    void processInput();
    void update(float t, float dt);
    void render();

private:
    Window& window;
    Renderer renderer;
    Shader shader;
    Camera camera;
    glm::mat4 model;

    Light light;
    // Shared mesh for all cubes.
    std::shared_ptr<Mesh> playerMesh;
    // A collection of cubes.
    std::vector<Entity> cubes;
};

#endif // GAME_H

