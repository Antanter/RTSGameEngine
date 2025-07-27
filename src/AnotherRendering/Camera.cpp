#include "Camera.hpp"
#include "../GameLogic/InputAndController/InputHandler.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec2 position, float zoom) : position(position), zoom(zoom) {}
Camera::~Camera() {}

void Camera::initInputCallbacks() {
    InputHandler::onKeyDown(GLFW_KEY_W, [this]() { moveDelta.y +=  1.0f; });
    InputHandler::onKeyDown(GLFW_KEY_S, [this]() { moveDelta.y += -1.0f; });
    InputHandler::onKeyDown(GLFW_KEY_A, [this]() { moveDelta.x += -1.0f; });
    InputHandler::onKeyDown(GLFW_KEY_D, [this]() { moveDelta.x +=  1.0f; });

    InputHandler::onKeyUp(GLFW_KEY_W,   [this]() { moveDelta.y -=  1.0f; });
    InputHandler::onKeyUp(GLFW_KEY_S,   [this]() { moveDelta.y -= -1.0f; });
    InputHandler::onKeyUp(GLFW_KEY_A,   [this]() { moveDelta.x -= -1.0f; });
    InputHandler::onKeyUp(GLFW_KEY_D,   [this]() { moveDelta.x -=  1.0f; });

    InputHandler::onMouseScroll([this](double, double yoff) {
        processScroll(yoff);
    });
}

void Camera::Init() {
    initInputCallbacks();
}

glm::mat4 Camera::getViewProjection(int screenWidth, int screenHeight) const {
    glm::mat4 projection = glm::ortho(
        0.0f, (float)screenWidth,
        0.0f, (float)screenHeight,
        -1.0f, 1.0f
    );

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

    return projection * view;
}

AABB Camera::getWorldBounds(int screenWidth, int screenHeight) const {
    float halfWidth  = (screenWidth  / zoom) * 0.5f;
    float halfHeight = (screenHeight / zoom) * 0.5f;

    glm::vec2 min = position - glm::vec2(halfWidth, halfHeight);
    glm::vec2 max = position + glm::vec2(halfWidth, halfHeight);

    return AABB{ min, max };
}

void Camera::move(const glm::vec2& delta) {
    position += delta;
}

void Camera::changeZoom(float factor) {
    zoom *= factor;
    if (zoom < LOWER_BOUND) zoom = LOWER_BOUND;
    if (zoom > UPPER_BOUND) zoom = UPPER_BOUND;
}

void Camera::update(float deltaTime) {
    if (moveDelta != glm::vec2(0.0f)) {
        glm::vec2 dir = glm::normalize(moveDelta);
        position += dir * sensitivity * deltaTime / zoom;
    }
}

void Camera::processScroll(double yoffset) {
    changeZoom(1.0f + yoffset * 0.1f);
}