#pragma once

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "camera.hpp"
#include "renderable.hpp"
#include "window.hpp"

class Renderer {
    private:

    void initGLFW();
    void initGLAD();
    void initCallbacks();
    void configureOpenGL();

    Window window;
    Camera camera;
    int width, height;
    glm::mat4 orthoProj;
    std::vector<Renderable> renderQueue;

    public:

    Renderer(int width, int height, const char* title = "RTS Engine");
    ~Renderer();

    void renderFrame(float deltaTime);
    void addObject(std::shared_ptr<Renderable> obj, float zLayer = 0.0f, bool isFixed = false);
};