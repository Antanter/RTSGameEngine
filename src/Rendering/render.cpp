#include "render.hpp"
#include <glad/glad.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(int w, int h, const char* title)
  : width(w), height(h), camera()
{
    initGLFW();
    window.initWindow(title, w, h);
    initGLAD();
    initCallbacks();
    configureOpenGL();
}

Renderer::~Renderer() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void Renderer::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Renderer::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        window.destroy();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::initCallbacks() {
    glfwSetWindowUserPointer(window, &camera);
    glfwSetScrollCallback(window, [](GLFWwindow* win, double xoff, double yoff) {
        auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
        cam->processScroll(yoff);
    });
}

void Renderer::configureOpenGL() {
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    orthoProj = glm::ortho(0.0f, float(width), 0.0f, float(height));
}

void Renderer::addObject(std::shared_ptr<Renderable> obj, float zLayer, bool isFixed) {
    renderQueue.emplace_back(std::move(obj), zLayer, isFixed);
}

void Renderer::renderFrame(float deltaTime) {
    glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera.update(deltaTime);
    auto vp = camera.getViewProjection(width, height);
    std::sort(renderQueue.begin(), renderQueue.end(), [](auto &a, auto &b) {
        return a.zLayer < b.zLayer;
    });

    for (auto& item : renderQueue) {
        item.render(camera.getViewProjection(width, height));
    }

    renderQueue.clear();
    glfwSwapBuffers(window);
}