#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    
    Camera(glm::vec3 position);
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    void setAspectRatio(float ar);
    void orbit(const glm::vec3& center, float radius, float time);
    void update(const float t);

private:
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

#endif // CAMERA_H
