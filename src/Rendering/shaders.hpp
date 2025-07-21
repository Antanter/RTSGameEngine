#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader {
    private:

    GLuint programID;

    std::string loadSource(const std::string& filePath) const;
    GLuint compileShader(const std::string& source, GLenum type) const;
    void   checkCompileErrors(GLuint shader, const std::string& type) const;

    public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;

    void setUniform(const std::string& name, bool value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, const glm::vec2& value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::mat4& mat) const;

    GLuint ID() const { return programID; }
};
