#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) 
    : position(position), target(glm::vec3(0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), 
      fov(45.0f), aspectRatio(800.0f / 600.0f), nearPlane(0.1f), farPlane(100.0f) {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setAspectRatio(float ar) {
    aspectRatio = ar;
}

void Camera::orbit(const glm::vec3& center, float radius, float time) {
    float angle = time * 0.5f;  // Rotate slowly over time
    position.x = center.x + radius * cos(angle);
    position.z = center.z + radius * sin(angle);
    position.y = center.y;
}

void Camera::update(const float t) {
    float PI = 3.14159f;
    float freq = 1.0/5;
    float phase = (2*PI*t*freq);
    float c = glm::cos(phase);
    float s = sin(phase);
    glm::vec3 base(0,0,5);
    position = base + glm::vec3(c,s,0);
}