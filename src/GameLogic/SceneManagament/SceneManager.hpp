#pragma once

#include "Scene.hpp"
#include <unordered_map>
#include <memory>

class SceneManager {
    private:

    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::unordered_map<std::string, std::string> filepaths;
    std::vector<std::shared_ptr<Scene>> activeScenes;
    
    public:
    ~SceneManager() = default;

    void Init();

    void addScene(const std::string& name, const std::string& filepath);
    void setActive(const std::string& name);
    void changeScene(const std::string& name);
    void update();

    void stopAll();
};
