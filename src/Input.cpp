#include "Input.h"

glm::quat Input::rotation(1.0f, 0.0f, 0.0f, 0.0f); // Identity quaternion

glm::vec2 lastMousePos;
glm::vec3 axis(1.0f, 0.0f, 0.0f);
bool rotating = false;

void Input::setupCallbacks(GLFWwindow* window) {
        glfwSetKeyCallback(window, Input::keyCallback);
        glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
        glfwSetCursorPosCallback(window, Input::cursorPositionCallback);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Mouse callback for quaternion rotation
void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            rotating = true;
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            lastMousePos = glm::vec2(x, y);
        } else if (action == GLFW_RELEASE) {
            rotating = false;
        }
    }
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (rotating) {
        glm::vec2 newMousePos = glm::vec2(xpos, ypos);
        glm::vec2 delta = newMousePos - lastMousePos;

        float angle = glm::length(delta) * 0.005f;
        if (angle < 0.000001f)
            return;
        glm::vec3 axis = glm::normalize(glm::vec3(delta.y, delta.x, 0.0f));


        rotation = glm::normalize(glm::angleAxis(angle, axis) * rotation);
        lastMousePos = newMousePos;
        //std::cout << "Mouse moved: " << xpos << ", " << ypos << std::endl;
        //std::cout << "last mouse pos: " << rotation.x << std::endl;
    }
}
