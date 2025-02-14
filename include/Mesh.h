#ifndef MESH_H
#define MESH_H

//#include <glad/glad.h>
#include "GLCommon.h"
#include <vector>

class Mesh {
public:
    // Constructs the mesh from vertex data and index data.
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    // Draws the mesh. Assumes an appropriate shader is already in use.
    void draw() const;

private:
    //GLuint VAO, VBO, EBO; T
    unsigned int VAO, VBO, EBO; // TODO: Fix <glad/glad.h> redefinition issue
    unsigned int indexCount;
};

#endif // MESH_H

