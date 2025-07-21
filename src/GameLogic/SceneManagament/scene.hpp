// scene.hpp
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

enum class EventType {
    SLUG,
    ACTION,
    DIALOGUE,
    SFX,
    CAMERA,
    UNKNOWN
};

struct SceneEvent {
    EventType type;
    std::string arg1;
    std::string arg2;
    std::string text;
};

class Scene {
    private:
    
    std::string name;
    std::vector<SceneEvent> events;
    size_t currentIndex = 0;

    EventType parseType(const std::string& token);
    SceneEvent parseLine(const std::string& line);
    
    public:
    Scene(const std::string& name);
    bool loadFromFile(const std::string& filepath);
    void reset();
    bool hasNext() const;
    SceneEvent next();
};
