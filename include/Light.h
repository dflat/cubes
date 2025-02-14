#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Shader.h" 

class Light {
public:
    /// Default constructor. Initializes the light at the origin with white color and unit intensity.
    Light();

    Light(const glm::vec3& position);

    /// @param position The world-space position of the light.
    Light(const glm::vec3& position, const glm::vec3& ambient,
                                     const glm::vec3& diffuse,
                                     const glm::vec3& specular);

    /// This function should be called every frame.
    void update(float t, float dt);

    /// Applies the light’s properties to the given shader by setting the corresponding uniforms.
    void apply(Shader& shader) const;

    // Accessors and mutators.
    void setPosition(const glm::vec3& position);

    const glm::vec3& getPosition() const;

private:
    glm::vec3 position;

    // Colors for each lighting component.
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Attenuation factors.
    float constant = 1.0f;
    float linear = 1.0f;
    float quadratic = 1.0f;

};

#endif // LIGHT_H

