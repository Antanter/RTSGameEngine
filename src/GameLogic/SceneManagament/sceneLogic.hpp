#pragma once

#include "scene.hpp"

class SceneManager {
public:
    SceneManager() = default;
    ~SceneManager() = default;

    bool addScene(const std::string& name, const std::string& filepath);
    bool setActive(const std::string& name);
    void update();
    void render();

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
};
