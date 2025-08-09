#include "InputHandler.hpp"

GLFWwindow* InputHandler::window = nullptr;
std::unordered_map<int, bool> InputHandler::keyStates;
std::unordered_map<int, bool> InputHandler::mouseButtonStates;
glm::dvec2 InputHandler::mousePosition = glm::dvec2(0.0);

std::unordered_map<int, std::function<void()>> InputHandler::keyDownCallbacks;
std::unordered_map<int, std::function<void()>> InputHandler::keyUpCallbacks;
std::unordered_map<int, std::function<void()>> InputHandler::mouseButtonDownCallbacks;
std::unordered_map<int, std::function<void()>> InputHandler::mouseButtonUpCallbacks;
std::function<void(double, double)> InputHandler::mouseMoveCallback = nullptr;
std::function<void(double, double)> InputHandler::mouseScrollCallback = nullptr;

void InputHandler::Init(GLFWwindow* win) {
    window = win;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void InputHandler::pollEvents() {
    glfwPollEvents();
}

void InputHandler::onKeyDown(int key, std::function<void()> callback) {
    keyDownCallbacks[key] = callback;
}

void InputHandler::onKeyUp(int key, std::function<void()> callback) {
    keyUpCallbacks[key] = callback;
}

bool InputHandler::isKeyPressed(int key) {
    return keyStates[key];
}

void InputHandler::onMouseButtonDown(int button, std::function<void()> callback) {
    mouseButtonDownCallbacks[button] = callback;
}

void InputHandler::onMouseButtonUp(int button, std::function<void()> callback) {
    mouseButtonUpCallbacks[button] = callback;
}

void InputHandler::onMouseMove(std::function<void(double, double)> callback) {
    mouseMoveCallback = callback;
}

void InputHandler::onMouseScroll(std::function<void(double, double)> callback) {
    mouseScrollCallback = callback;
}

bool InputHandler::isMouseButtonPressed(int button) {
    return mouseButtonStates[button];
}

glm::dvec2 InputHandler::getMousePosition() {
    return mousePosition;
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyStates[key] = true;
        if (keyDownCallbacks.find(key) != keyDownCallbacks.end()) {
            keyDownCallbacks[key]();
        }
    }
    if (action == GLFW_RELEASE) {
        keyStates[key] = false;
        if (keyUpCallbacks.find(key) != keyUpCallbacks.end()) {
            keyUpCallbacks[key]();
        }
    }
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        mouseButtonStates[button] = true;
        if (mouseButtonDownCallbacks.find(button) != mouseButtonDownCallbacks.end()) {
            mouseButtonDownCallbacks[button]();
        }
    }
    if (action == GLFW_RELEASE) {
        mouseButtonStates[button] = false;
        if (mouseButtonUpCallbacks.find(button) != mouseButtonUpCallbacks.end()) {
            mouseButtonUpCallbacks[button]();
        }
    }
}

void InputHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    mousePosition = {xpos, ypos};
    if (mouseMoveCallback) {
        mouseMoveCallback(xpos, ypos);
    }
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (mouseScrollCallback) {
        mouseScrollCallback(xoffset, yoffset);
    }
}
