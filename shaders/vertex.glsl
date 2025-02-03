#version 330 core
layout (location = 0) in vec3 aPos;      // Position
layout (location = 1) in vec3 aNormal;   // Normal
layout (location = 2) in vec3 aColor;    // Color

out vec3 FragPos;
out vec3 Normal;
out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Transform the vertex position to world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    // Transform the normal with the inverse transpose of the model matrix
    Normal = mat3(transpose(inverse(model))) * aNormal;
    ourColor = aColor;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
