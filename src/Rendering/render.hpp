#pragma once

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "camera.hpp"

class Renderable {
    public:
    virtual ~Renderable() = default;

    virtual void render(const glm::mat4& projection, const glm::mat4& view) = 0;
};

struct RenderItem {
    std::shared_ptr<Renderable> object;
    float z;
    bool fixed;
    RenderItem(std::shared_ptr<Renderable> obj, float zLayer, bool isFixed)
        : object(std::move(obj)), z(zLayer), fixed(isFixed) {}
};

class Renderer {
    private:

    void initGLFW();
    void initWindow(const char* title);
    void initGLAD();
    void initCallbacks();
    void configureOpenGL();

    void renderFrame(float deltaTime);

    GLFWwindow* window = nullptr;
    Camera camera;
    int width;
    int height;
    glm::mat4 orthoProj;
    std::vector<RenderItem> renderQueue;

    public:

    Renderer(int width, int height, const char* title = "RTS Engine");
    ~Renderer();

    void runLoop();
    void addObject(std::shared_ptr<Renderable> obj, float zLayer = 0.0f, bool isFixed = false);
};