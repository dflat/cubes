#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
//#include <glad/glad.h>
#include <glm/vec3.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use();
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3&);
    void setUniform(const std::string& name, const float* matrix); // For transformations

    ~Shader();

private:
    std::string readFile(const std::string& filePath);
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif

