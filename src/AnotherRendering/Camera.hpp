#pragma once

#include <glm/glm.hpp>

struct AABB {
    glm::vec2 min;
    glm::vec2 max;

    bool contains(const glm::vec2& point) const {
        return point.x >= min.x && point.x <= max.x &&
               point.y >= min.y && point.y <= max.y;
    }

    bool intersects(const AABB& other) const {
        return !(max.x < other.min.x || min.x > other.max.x ||
                 max.y < other.min.y || min.y > other.max.y);
    }
};

class Camera {
    private:

    static constexpr float LOWER_BOUND = 0.01f;
    static constexpr float UPPER_BOUND = 10.0f;

    float sensitivity;

    glm::vec2 position;
    glm::vec2 moveDelta;
    float zoom;

    void initInputCallbacks();

    public:

    Camera(glm::vec2 position, float zoom);
    ~Camera();

    void Init();

    glm::mat4 getViewProjection(int screenWidth, int screenHeight) const;
    AABB getWorldBounds(int screenWidth, int screenHeight) const;

    void update(float deltaTime);
    void move(const glm::vec2& delta);
    void changeZoom(float factor);
    void processScroll(double yoffset);
};
