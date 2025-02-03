#include "Game.h"

Game::Game(Window& win)
    : window(win),
      shader("shaders/vertex.glsl", "shaders/fragment.glsl"),
      camera(glm::vec3(0.0f, 0.0f, 5.0f)),
      model(glm::mat4(1.0f)),
      lightPos(1.2f, 1.0f, 2.0f) {}

bool Game::init() {
    glfwSetFramebufferSizeCallback(window.window, Window::framebufferSizeCallback);
    glfwSetWindowUserPointer(window.window, &camera); // store pointer to camera on window object
    Input::setupCallbacks(window.window);
    renderer.init();
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
    camera.update(t);
    model = glm::mat4_cast(Input::rotation);
}

void Game::render() {
    renderer.clear();
    shader.use();
    shader.setUniform("model", glm::value_ptr(model));
    shader.setUniform("view", glm::value_ptr(camera.getViewMatrix()));
    shader.setUniform("projection", glm::value_ptr(camera.getProjectionMatrix()));
    shader.setUniform("lightPos", lightPos);
    shader.setUniform("viewPos", camera.position);
    cube.draw(shader);
}