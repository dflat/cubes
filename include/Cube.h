#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shader.h"

class Cube {
private:
    GLuint VAO, VBO, EBO;

public:
    static float vertices[9*4*6];
    static unsigned int indices[3*2*6];

    Cube();
    ~Cube();
    void draw(Shader& shader);

};

#endif
