#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>
#include <utility>
#include <glm/glm.hpp>

class InputHandler {
    private:

    static GLFWwindow* window;

    static std::unordered_map<int, bool> keyStates;
    static std::unordered_map<int, bool> mouseButtonStates;
    static glm::dvec2 mousePosition;

    static std::unordered_map<int, std::function<void()>> keyDownCallbacks;
    static std::unordered_map<int, std::function<void()>> keyUpCallbacks;
    static std::unordered_map<int, std::function<void()>> mouseButtonDownCallbacks;
    static std::unordered_map<int, std::function<void()>> mouseButtonUpCallbacks;
    static std::function<void(double, double)> mouseMoveCallback;
    static std::function<void(double, double)> mouseScrollCallback;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    public:

    static void init(GLFWwindow* win);

    static void onKeyDown(int key, std::function<void()> callback);
    static void onKeyUp(int key, std::function<void()> callback);
    static bool isKeyPressed(int key);

    static void onMouseButtonDown(int button, std::function<void()> callback);
    static void onMouseButtonUp(int button, std::function<void()> callback);
    static void onMouseMove(std::function<void(double, double)> callback);
    static void onMouseScroll(std::function<void(double, double)> callback);
    static bool isMouseButtonPressed(int button);
    static glm::dvec2 getMousePosition();

    static void pollEvents();
};
