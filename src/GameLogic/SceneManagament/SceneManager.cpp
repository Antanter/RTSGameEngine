#include "SceneManager.hpp"
#include <iostream>

void SceneManager::Init() {

}

void SceneManager::addScene(const std::string& name, const std::string& filepath) {
    auto scene = std::make_shared<Scene>(name);
    if (!scene->loadFromFile(filepath)) {
        std::cerr << "Failed to load scene from file: " << filepath << std::endl;
        return;
    }

    scenes[name] = scene;
    return;
}

void SceneManager::setActive(const std::string& name) {
    auto scene = scenes.find(name);
    if (scene == scenes.end()) {
        std::cerr << "Scene not found: " << name << std::endl;
        return;
    }

    activeScenes.push_back(scene->second);
    std::cout << "Activated scene: " << name << std::endl;

    return;
}

void SceneManager::update() {
    for (auto scene : scenes) {
        scene.second->update();
    }
}

void SceneManager::changeScene(const std::string& name) {
    auto scene = scenes.find(name);
    if (scene == scenes.end()) {
        std::cerr << "Scene not found: " << name << std::endl;
        return;
    }

    const std::string filepath = "scenes/" + name;
    std::shared_ptr<Scene> sceneToSave = scene->second;

    if (!sceneToSave->saveToFile(filepath)) {
        std::cerr << "Failed to save scene to file: " << filepath << std::endl;
    } else {
        std::cout << "Scene saved to: " << filepath << std::endl;
    }
}

void SceneManager::stopAll() {

}