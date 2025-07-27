#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>

struct ObjectInfo {
    std::string id;
    std::string type;
    glm::vec3 position;
    glm::vec3 rotation;
};

class Scene {
    private:
    std::string name;
    glm::vec3 cameraPosition;
    std::vector<ObjectInfo> objects;

    public:
    Scene(const std::string& name = "unnamed");

    bool loadFromFile(const std::string& filepath);
    bool saveToFile(const std::string& filepath) const;
    void reset();

    const std::string& getName() const;
    const glm::vec3& getCameraPosition() const;
    const std::vector<ObjectInfo>& getObjects() const;
};
