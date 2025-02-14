#include "Light.h"

// Default constructor: position at origin, white light with full intensity.
Light::Light() 
    : position(0.0f, 0.0f, 0.0f)
{
}

Light::Light(const glm::vec3 &position)
    : position(position)
{
}

Light::Light(const glm::vec3& position, const glm::vec3& ambient,
                                        const glm::vec3& diffuse,
                                        const glm::vec3& specular)
    : position(position),
      ambient(ambient),
      diffuse(diffuse),
      specular(specular)
{
}

void Light::update(float t, float dt) {
    float phase = 6.18f*0.125f*t;
    float r = 3;
    position.x = r*sin(phase);
    position.z = 0.6;//r*cos(phase);
    position.y = 0;
}

// Sets the light uniforms in the shader.
// It is considered good practice for an object to be responsible for updating its own shader parameters.
void Light::apply(Shader &shader) const {
    shader.setUniform("lightPos", position);
}

// Setter for position.
void Light::setPosition(const glm::vec3 &position) {
    this->position = position;
}

// Getter for position.
const glm::vec3& Light::getPosition() const {
    return position;
}
