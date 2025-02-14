#pragma once

#include <vector>
//#include <glm/glm.hpp> // For glm::vec3, glm::vec2, etc.

namespace GeometryData {

static std::vector<float> cubeVertices = {
        // Front face (red)
        -0.5f, -0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // bottom-left
         0.5f, -0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // bottom-right
         0.5f,  0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // top-right
        -0.5f,  0.5f,  0.5f,    0,  0, 1,    1, 0, 0,  // top-left

        // Back face (green)
         0.5f, -0.5f, -0.5f,    0,  0, -1,   1, 1, 1,  // bottom-left (when viewed from the back)
        -0.5f, -0.5f, -0.5f,    0,  0, -1,   1, 1, 1,  // bottom-right
        -0.5f,  0.5f, -0.5f,    0,  0, -1,   1, 1, 1,  // top-right
         0.5f,  0.5f, -0.5f,    0,  0, -1,   1, 1, 1,  // top-left

        // Left face (blue)
        -0.5f, -0.5f, -0.5f,   -1,  0,  0,   1, 1, 1,  // bottom-left
        -0.5f, -0.5f,  0.5f,   -1,  0,  0,   1, 1, 1,  // bottom-right
        -0.5f,  0.5f,  0.5f,   -1,  0,  0,   1, 1, 1,  // top-right
        -0.5f,  0.5f, -0.5f,   -1,  0,  0,   1, 1, 1,  // top-left

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
        -0.5f, -0.5f, -0.5f,    0, -1,  0,   1, 1, 1,  // bottom-left
         0.5f, -0.5f, -0.5f,    0, -1,  0,   1, 1, 1,  // bottom-right
         0.5f, -0.5f,  0.5f,    0, -1,  0,   1, 1, 1,  // top-right
        -0.5f, -0.5f,  0.5f,    0, -1,  0,   1, 1, 1   // top-left
    };

// Indices for drawing the 6 faces of the cube (2 triangles per face)
static std::vector<unsigned int> cubeIndices = {
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

}
