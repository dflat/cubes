#ifndef CUBE_H
#define CUBE_H

#include "Entity.h"
#include <glm/glm.hpp>

class Mesh; // Forward declaration if not already included in Entity.h

// The Cube class is a specialization of Entity. For now, it simply calls the Entity constructor.
class Cube : public Entity {
public:
    // Constructor: takes a pointer to the shared Mesh and an optional initial model matrix.
    Cube(Mesh* mesh, const glm::mat4& model = glm::mat4(1.0f));
    Cube(Mesh* mesh, const glm::vec3& position);
};

#endif // CUBE_H

