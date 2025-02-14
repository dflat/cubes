#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input {
public:
    static glm::quat rotation;
    static glm::vec2 lastMousePos;
    static glm::vec3 axis;
    static bool rotating;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void setupCallbacks(GLFWwindow* window);
};

#endif // INPUT_H