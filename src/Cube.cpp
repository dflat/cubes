#include "Cube.h"

Cube::Cube(Mesh* mesh, const glm::mat4& model)
    : Entity(mesh, model)
{
}

Cube::Cube(Mesh* mesh, const glm::vec3& position)
    : Entity(mesh, position)
{
}
