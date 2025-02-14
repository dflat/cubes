#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>
#include "GLCommon.h"
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use();
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3&);
    void setUniform(const std::string& name, const glm::mat4&); // For transformations

    ~Shader();

private:
    std::unordered_map<std::string, GLint> uniformLocationCache;

    std::string readFile(const std::string& filePath);
    void checkCompileErrors(unsigned int shader, const std::string& type);
    GLint getUniformLocation(const std::string& name);


};

#endif

