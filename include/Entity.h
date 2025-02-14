#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

class Mesh;
class Shader;

class Entity {
public:
    // Constructors
    Entity();
    explicit Entity(std::shared_ptr<Mesh> mesh);
    Entity(std::shared_ptr<Mesh> mesh, const glm::vec3& position);

    // Copy and move semantics
    /*
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& other) = delete;
    Entity(Entity&& other) noexcept;
    Entity& operator=(Entity&& other) noexcept;
    */

    // Destructor
    ~Entity();

    // Drawing
    void draw(Shader& shader) const;

    // Transformation methods
    void translate(const glm::vec3& translation);
    void rotate(const glm::quat& rotation);
    void scale(const glm::vec3& scaling);

    // Setters
    void setMesh(std::shared_ptr<Mesh> newMesh);
    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);
    void setScale(const glm::vec3& scale);

    // Getters
    Mesh* getMesh() const;
    glm::vec3 getPosition() const;
    glm::quat getOrientation() const;
    glm::vec3 getScale() const;
    const glm::mat4& getModelMatrix() const;

private:
    // Recalculate the model matrix
    void updateModelMatrix() const;

    // Member variables
    std::shared_ptr<Mesh> m_mesh;
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_scale;
    mutable glm::mat4 m_modelMatrix;
    mutable bool m_modelMatrixNeedsUpdate;
};

#endif // ENTITY_H
