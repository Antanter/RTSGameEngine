#pragma once

#include <string>
#include <glm/glm.hpp>

struct GLFWwindow;

class Window {
    private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
    Window(int width, int height, const char* title);
    ~Window();

    void Init();

    bool shouldClose() const;

    void pollEvents() const;
    void swapBuffers() const;

    int getWidth() const;
    int getHeight() const;
    glm::ivec2 getSize() const;
};
