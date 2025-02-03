#include "Window.h"
#include "Camera.h"
#include <iostream>

Window::Window(int w, int h, const char* t)
    : width(w), height(h), title(t), window(nullptr) {}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
    #endif

    glfwWindowHint(GLFW_SAMPLES, 4); // Set 4x MSAA (Adjust as needed) (TODO: make argument)

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

// Callback to adjust the viewport when the window is resized
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
   // Get the pointer to the Camera object (or other object holding the projection matrix)
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        // Recalculate the projection matrix with the new aspect ratio
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height); 
        camera->setAspectRatio(aspectRatio);
    }
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

float Window::getTime() {
    return glfwGetTime();
}

Window::~Window() {
    glfwTerminate();
}
