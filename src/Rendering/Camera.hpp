#pragma once

#include <glm/glm.hpp>

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

    Camera();
    ~Camera();

    glm::mat4 getViewProjection(int screenWidth, int screenHeight) const;

    void update(float deltaTime);
    void move(const glm::vec2& delta);
    void changeZoom(float factor);
    void processScroll(double yoffset);
};
