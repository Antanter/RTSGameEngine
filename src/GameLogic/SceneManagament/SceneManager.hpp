#pragma once

#include "Scene.hpp"
#include <unordered_map>
#include <memory>

class SceneManager {
    private:

    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::unordered_map<std::string, std::string> filepaths;
    std::shared_ptr<Scene> activeScene;
    
    public:
    ~SceneManager() = default;

    bool addScene(const std::string& name, const std::string& filepath);
    bool setActive(const std::string& name);
    void update(const std::string& name);

    std::shared_ptr<Scene> getScene() const;
};
