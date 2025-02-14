#include "GLCommon.h"
#include "Game.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "GeometryData.h"
#include "GeometryLoader.h"
#include "Entity.h"

Game::Game(Window& win)
    : window   {win},
      shader   {"shaders/vertex.glsl", "shaders/fragment.glsl"},
      camera   {glm::vec3(0.0f, 0.0f, 5.0f)},
      model    {glm::mat4(1.0f)},
      light    {},
      playerMesh {nullptr}
{
}

Game::~Game() {
    // Clean up the dynamically allocated mesh.
    //if (playerMesh)
    //    delete playerMesh;
}

bool Game::init() {
    glfwSetFramebufferSizeCallback(window.window, Window::framebufferSizeCallback);
    glfwSetWindowUserPointer(window.window, &camera); // store pointer to camera on window object
    Input::setupCallbacks(window.window);
    renderer.init();

    // Create the shared cube mesh using our vertex and index data.
    //cubeMesh = new Mesh(GeometryData::cubeVertices, GeometryData::cubeIndices);
    //auto mesh = std::make_unique<Mesh>(GeometryData::cubeVertices, GeometryData::cubeIndices);
    //Entity player(std::move(mesh), glm::vec3(0, 0, 0)); 
    //cubes.push_back(std::move(player));

    playerMesh = GeometryLoader::loadFromOBJ("assets/torus.obj");
    //cubes.push_back(Entity(mesh.get(), glm::vec3(0, 0, 0)));
    cubes.push_back(Entity(playerMesh, glm::vec3(0, 0, 0)));
    cubes.push_back(Entity(playerMesh, glm::vec3(-3, 0, 0)));
    cubes.push_back(Entity(playerMesh, glm::vec3(3, 0, 0)));
    // Create several Cube instances with different transforms.
    // Note: Cube is derived from Entity, and its constructor takes a Mesh pointer and an initial model matrix.
    //cubes.push_back( Cube(cubeMesh, glm::mat4(1.0f)) );  // Center cube.
    //cubes.push_back( Cube(cubeMesh, glm::vec3( 2.0f, 0.0f, 0.0f)) );
    //cubes.push_back( Cube(cubeMesh, glm::vec3(-2.0f, 0.0f, 0.0f)) );
    //cubes.push_back( Cube(cubeMesh, glm::translate(glm::mat4(1.0f), glm::vec3( 2.0f, 0.0f, 0.0f))) );
    //cubes.push_back( Cube(cubeMesh, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))) );

    //Light light = Light();
    light.setPosition(glm::vec3(0,1,0));

    return true;
}

void Game::run() {
    float lastFrameTime = 0.0f;
    while (!window.shouldClose()) {
        float currentFrameTime = window.getTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput();
        update(currentFrameTime, deltaTime);
        render();
        window.swapBuffers();
        window.pollEvents();
    }
}

void Game::processInput() {
    window.processInput();
}

void Game::update(float t, float dt) {
    // Update camera or any game logic here.
    camera.update(t);
    light.update(t, dt);
    light.apply(shader);

    // Optionally, update a global model matrix based on input (for example, from Input::rotation).
    model = glm::mat4_cast(Input::rotation);

    int i = 0;
    for (auto& cube : cubes) {
        //cube.setPosition(glm::vec3(1,0,0));
        auto q = Input::rotation;
        for (int j = 0; j < i % 3; j++)
            q *= q;
        //cube.position.x += .01f*Input::rotation.x;
        //cube.setOrientation(Input::rotation);
        cube.setOrientation(q);
        i += 1;
        //glm::mat4 cubeModel = cube.getModelMatrix() * model;
        //cube.setModelMatrix(cubeModel);
    }
}

void Game::render() {
    renderer.clear();

    // Activate the shader.
    shader.use();

    // Set uniforms that are common to all cubes.
    shader.setUniform("view", camera.getViewMatrix());
    shader.setUniform("projection", camera.getProjectionMatrix());
    shader.setUniform("viewPos", camera.position);

    // Draw each cube. Each cube (via its Entity base class) will set its own model matrix.
    for (auto& cube : cubes) {
        cube.draw(shader);
    }
}

