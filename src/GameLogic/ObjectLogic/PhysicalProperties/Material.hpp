#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "../../../Rendering/shaders.hpp"

class Texture {
    public:

    unsigned int id;
    std::string type;
    std::string path;

    Texture(const std::string& path, const std::string& type);
    void load();
};

class Material {
    private:
    std::shared_ptr<Shader> shader;
    
    public:
    glm::vec3 baseColor {1.0f, 1.0f, 1.0f};
    float     shininess = 32.0f;

    std::shared_ptr<Texture> diffuseTexture;

    Material(std::shared_ptr<Shader> shader);
    ~Material() = default;

    void apply() const;
};