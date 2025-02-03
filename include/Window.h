#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* window;
    int width, height;
    const char* title;
    
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    Window(int w, int h, const char* t);
    bool init();
    bool shouldClose();
    void processInput();
    void swapBuffers();
    void pollEvents();
    float getTime();
    ~Window();

};

#endif // WINDOW_H
