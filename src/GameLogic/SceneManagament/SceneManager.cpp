#include "SceneManager.hpp"
#include <iostream>

bool SceneManager::addScene(const std::string& name, const std::string& filepath) {
    auto scene = std::make_shared<Scene>(name);
    if (!scene->loadFromFile(filepath)) {
        std::cerr << "Failed to load scene from file: " << filepath << std::endl;
        return false;
    }

    scenes[name] = scene;
    return true;
}

bool SceneManager::setActive(const std::string& name) {
    auto it = scenes.find(name);
    if (it == scenes.end()) {
        std::cerr << "Scene not found: " << name << std::endl;
        return false;
    }

    activeScene = it->second;
    std::cout << "Activated scene: " << name << std::endl;

    return true;
}

void SceneManager::update(const std::string& name) {
    auto it = scenes.find(name);
    if (it == scenes.end()) {
        std::cerr << "Scene not found: " << name << std::endl;
        return;
    }

    const std::string filepath = "scenes/" + name;
    std::shared_ptr<Scene> sceneToSave = it->second;

    if (!sceneToSave->saveToFile(filepath)) {
        std::cerr << "Failed to save scene to file: " << filepath << std::endl;
    } else {
        std::cout << "Scene saved to: " << filepath << std::endl;
    }
}

std::shared_ptr<Scene> SceneManager::getScene() const {
    return activeScene;
}