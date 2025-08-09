#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>

#include "../ObjectLogic/GameObject.hpp"

class Scene {
    private:
    std::string name;
    glm::vec3 cameraPosition;
    std::vector<GameObject> objects;

    public:
    Scene(const std::string& name = "unnamed");

    bool loadFromFile(const std::string& filepath);
    bool saveToFile(const std::string& filepath) const;

    void reset();
    void update();

    const std::string& getName() const;
    const glm::vec3& getCameraPosition() const;
    const std::vector<GameObject>& getObjects() const;
};
