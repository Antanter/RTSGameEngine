#pragma once
#include <glm/glm.hpp>
#include <string>

class Material {
    private:
    glm::vec3 albedoColor = glm::vec3(1.0f);
    float metallic = 0.0f;
    float roughness = 0.5f;
    float alpha = 1.0f;

    std::string diffuseTexturePath;
    std::string normalTexturePath;

    public:

    void bind();
};
