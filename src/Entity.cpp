#include "Entity.h"
#include "Shader.h"
#include "Mesh.h"
#include <glm/gtx/quaternion.hpp>

Entity::Entity() 
    : m_position(0.0f),
      m_orientation(glm::identity<glm::quat>()),
      m_scale(1.0f),
      m_modelMatrix(1.0f),
      m_modelMatrixNeedsUpdate(true) 
{}

Entity::Entity(std::shared_ptr<Mesh> mesh)
    : m_mesh(std::move(mesh)),
      m_position(0.0f),
      m_orientation(glm::identity<glm::quat>()),
      m_scale(1.0f),
      m_modelMatrix(1.0f),
      m_modelMatrixNeedsUpdate(true)
{}

Entity::Entity(std::shared_ptr<Mesh> mesh, const glm::vec3& position)
    : m_mesh(std::move(mesh)),
      m_position(position),
      m_orientation(glm::identity<glm::quat>()),
      m_scale(1.0f),
      m_modelMatrix(1.0f),
      m_modelMatrixNeedsUpdate(true)
{}

/*
// Move constructor
Entity::Entity(Entity&& other) noexcept = default;

// Move assignment operator
Entity& Entity::operator=(Entity&& other) noexcept = default;
*/

// Destructor
Entity::~Entity() = default;

void Entity::draw(Shader& shader) const {
    shader.use();
    
    // Lazily update model matrix if needed
    if (m_modelMatrixNeedsUpdate) {
        updateModelMatrix();
    }
    
    // Pass the model matrix to the shader
    shader.setUniform("model", m_modelMatrix);

    // Draw the associated mesh
    if (m_mesh) {
        m_mesh->draw();
    }
}

void Entity::translate(const glm::vec3& translation) {
    m_position += translation;
    m_modelMatrixNeedsUpdate = true;
}

void Entity::rotate(const glm::quat& rotation) {
    m_orientation = rotation * m_orientation;
    m_modelMatrixNeedsUpdate = true;
}

void Entity::scale(const glm::vec3& scaling) {
    m_scale *= scaling;
    m_modelMatrixNeedsUpdate = true;
}

void Entity::setMesh(std::shared_ptr<Mesh> newMesh) {
    m_mesh = std::move(newMesh);
}

void Entity::setPosition(const glm::vec3& position) {
    m_position = position;
    m_modelMatrixNeedsUpdate = true;
}

void Entity::setOrientation(const glm::quat& orientation) {
    m_orientation = orientation;
    m_modelMatrixNeedsUpdate = true;
}

void Entity::setScale(const glm::vec3& scale) {
    m_scale = scale;
    m_modelMatrixNeedsUpdate = true;
}

Mesh* Entity::getMesh() const {
    return m_mesh.get();
}

glm::vec3 Entity::getPosition() const {
    return m_position;
}

glm::quat Entity::getOrientation() const {
    return m_orientation;
}

glm::vec3 Entity::getScale() const {
    return m_scale;
}

const glm::mat4& Entity::getModelMatrix() const {
    if (m_modelMatrixNeedsUpdate) {
        updateModelMatrix();
    }
    return m_modelMatrix;
}

void Entity::updateModelMatrix() const {
    // Construct model matrix from translation, rotation, and scale
    m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position) 
                  * glm::mat4_cast(m_orientation) 
                  * glm::scale(glm::mat4(1.0f), m_scale);
    
    m_modelMatrixNeedsUpdate = false;
}
