#include "Scene.hpp"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Scene::Scene(const std::string& name) : name(name) {}

void Scene::reset() {
    name.clear();
}

void Scene::update() {
    for (auto object : objects) {
        object.update();
    }
}

bool Scene::loadFromFile(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return false;
    }

    json j;
    in >> j;

    name = j.value("name", "unnamed_scene");

    auto cam = j.value("cameraPosition", std::vector<float>{0, 0, 0});
    if (cam.size() == 3) {
        cameraPosition = glm::vec3(cam[0], cam[1], cam[2]);
    }

    objects.clear();
    // for (const auto& jobj : j["objects"]) {
    //     GameObject obj;
    //     obj.id = jobj.value("id", "");
    //     obj.type = jobj.value("type", "");

    //     auto pos = jobj.value("position", std::vector<float>{0, 0, 0});
    //     auto rot = jobj.value("rotation", std::vector<float>{0, 0, 0});
    //     if (pos.size() == 3) obj.position = glm::vec3(pos[0], pos[1], pos[2]);
    //     if (rot.size() == 3) obj.rotation = glm::vec3(rot[0], rot[1], rot[2]);

    //     objects.push_back(obj);
    // }

    return true;
}

bool Scene::saveToFile(const std::string& filepath) const {
    json j;
    j["name"] = name;
    j["cameraPosition"] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };

    j["objects"] = json::array();
    // for (const auto& obj : objects) {
    //     json o;
    //     o["id"] = obj.id;
    //     o["type"] = obj.type;
    //     o["position"] = { obj.position.x, obj.position.y, obj.position.z };
    //     o["rotation"] = { obj.rotation.x, obj.rotation.y, obj.rotation.z };
    //     j["objects"].push_back(o);
    // }

    std::ofstream out(filepath);
    if (!out.is_open()) {
        std::cerr << "Failed to write file: " << filepath << std::endl;
        return false;
    }

    out << j.dump(4);
    return true;
}

const std::string& Scene::getName() const {
    return name;
}

const glm::vec3& Scene::getCameraPosition() const {
    return cameraPosition;
}