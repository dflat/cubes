#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

// Forward-declare your Shader class if needed, or include its header.
#include "Shader.h"

class Entity {
public:
    // Constructs an entity that references a mesh and starts with an identity model matrix.
    Entity(Mesh* mesh, const glm::mat4& model = glm::mat4(1.0f));
    Entity(Mesh* mesh, const glm::vec3& position);

    // Draws the entity using its mesh and sets the model matrix uniform.
    void draw(Shader& shader) const;

    // Setters and getters for the model matrix
    void setModelMatrix(const glm::mat4& model);
    const glm::mat4 getModelMatrix() const;

    void setOrientation(const glm::quat& q);
    void setPosition(const glm::vec3& T);
    // Other transformation or instance-specific functions can be added here,
    // such as translation, rotation, scaling, etc.

    glm::vec3 position;

private:
    Mesh* mesh;         // Shared mesh data (geometry, buffers, etc.)
    glm::mat4 model;    // Model matrix representing the entity's transformation
    glm::quat orientation;
};

#endif // ENTITY_H

