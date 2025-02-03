#include <glad/glad.h>
#include "Cube.h"

Cube::Cube() {
        // Set up vertex data, buffers, and configure vertex attributes
        glGenVertexArrays(1, &VAO);  
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind and set the vertex buffer(s) and attribute pointers.
        glBindVertexArray(VAO);

        // Vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex attributes:
        // Each vertex has 9 floats: 3 for position, 3 for normal, 3 for color.
        GLsizei stride = 9 * sizeof(float);
        // Position attribute (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
        // Normal attribute (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // Color attribute (location = 2)
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
}

Cube::~Cube() {
    // Cleanup: delete allocated resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::draw(Shader& shader) {
        // Bind the VAO and draw the cube using indices
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

float Cube::vertices[] = {
        // Front face (red)
        -0.5f, -0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // bottom-left
         0.5f, -0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // bottom-right
         0.5f,  0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // top-right
        -0.5f,  0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // top-left

        // Back face (green)
         0.5f, -0.5f, -0.5f,    0,  0, -1,   0, 1, 0,  // bottom-left (when viewed from the back)
        -0.5f, -0.5f, -0.5f,    0,  0, -1,   0, 1, 0,  // bottom-right
        -0.5f,  0.5f, -0.5f,    0,  0, -1,   0, 1, 0,  // top-right
         0.5f,  0.5f, -0.5f,    0,  0, -1,   0, 1, 0,  // top-left

        // Left face (blue)
        -0.5f, -0.5f, -0.5f,   -1,  0,  0,   0, 0, 1,  // bottom-left
        -0.5f, -0.5f,  0.5f,   -1,  0,  0,   0, 0, 1,  // bottom-right
        -0.5f,  0.5f,  0.5f,   -1,  0,  0,   0, 0, 1,  // top-right
        -0.5f,  0.5f, -0.5f,   -1,  0,  0,   0, 0, 1,  // top-left

        // Right face (yellow)
         0.5f, -0.5f,  0.5f,    1,  0,  0,   1, 1, 0,  // bottom-left
         0.5f, -0.5f, -0.5f,    1,  0,  0,   1, 1, 0,  // bottom-right
         0.5f,  0.5f, -0.5f,    1,  0,  0,   1, 1, 0,  // top-right
         0.5f,  0.5f,  0.5f,    1,  0,  0,   1, 1, 0,  // top-left

        // Top face (cyan)
        -0.5f,  0.5f,  0.5f,    0,  1,  0,   0, 1, 1,  // bottom-left
         0.5f,  0.5f,  0.5f,    0,  1,  0,   0, 1, 1,  // bottom-right
         0.5f,  0.5f, -0.5f,    0,  1,  0,   0, 1, 1,  // top-right
        -0.5f,  0.5f, -0.5f,    0,  1,  0,   0, 1, 1,  // top-left

        // Bottom face (magenta)
        -0.5f, -0.5f, -0.5f,    0, -1,  0,   1, 0, 1,  // bottom-left
         0.5f, -0.5f, -0.5f,    0, -1,  0,   1, 0, 1,  // bottom-right
         0.5f, -0.5f,  0.5f,    0, -1,  0,   1, 0, 1,  // top-right
        -0.5f, -0.5f,  0.5f,    0, -1,  0,   1, 0, 1   // top-left
    };

// Indices for drawing the 6 faces of the cube (2 triangles per face)
unsigned int Cube::indices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    8, 9, 10,
    10, 11, 8,
    // Right face
    12, 13, 14,
    14, 15, 12,
    // Top face
    16, 17, 18,
    18, 19, 16,
    // Bottom face
    20, 21, 22,
    22, 23, 20
};
