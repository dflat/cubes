#include "Entity.h"

Entity::Entity(Mesh* mesh, const glm::mat4& model)
    : mesh(mesh), model(model), orientation(1,0,0,0), position(0,0,0)
{}

Entity::Entity(Mesh* mesh, const glm::vec3& position)
    : mesh(mesh), model(glm::mat4(1.0f)), orientation(1,0,0,0), position(position)
{}

void Entity::draw(Shader& shader) const {
    // Activate shader
    shader.use();

    // Pass the model matrix to the shader
    // Assumes that your shader has a uniform called "model" and a method setMat4
    shader.setUniform("model", getModelMatrix());

    // Draw the associated mesh
    if(mesh)
        mesh->draw();
}

void Entity::setModelMatrix(const glm::mat4& newModel) {
    model = newModel;
}

void Entity::setOrientation(const glm::quat& q) {
    orientation = q;
}
void Entity::setPosition(const glm::vec3& T) {
    position = T;
}

const glm::mat4 Entity::getModelMatrix() const {
    //model = glm::translate(glm::mat4_cast(orientation), position);
    glm::mat4 R = glm::mat4_cast(orientation);
    R[3] = glm::vec4(position, 1.0f);
    return R;
}

