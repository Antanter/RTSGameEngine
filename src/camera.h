#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
    public:

    glm::vec2 position;
    float zoom;
    float speed = 500.0f;

    Camera()
        : position(0.0f, 0.0f), zoom(1.0f) {}

    glm::mat4 getViewProjection(int screenWidth, int screenHeight) const {
        glm::mat4 projection = glm::ortho(
            0.0f, (float)screenWidth,
            0.0f, (float)screenHeight,
            -1.0f, 1.0f
        );

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
        view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

        return projection * view;
    }

    void move(const glm::vec2& delta) {
        position += delta;
    }

    void changeZoom(float factor) {
        zoom *= factor;
        if (zoom < 0.1f) zoom = 0.1f;
        if (zoom > 10.0f) zoom = 10.0f;
    }

    void processKeyboard(GLFWwindow* window, float speed, float deltaTime) {
        glm::vec2 moveDelta(0.0f);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveDelta.y += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveDelta.y -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) moveDelta.x -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) moveDelta.x += 1.0f;

        if (moveDelta != glm::vec2(0.0f)) {
            moveDelta = glm::normalize(moveDelta);
            move(moveDelta * speed * deltaTime / zoom);
        }
    }

    void processScroll(double yoffset) {
        changeZoom(1.0f + yoffset * 0.1f);
    }
};
