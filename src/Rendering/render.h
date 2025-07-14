#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

class Renderable {
    public:
    virtual void render(float screenLeft, float screenRight, float screenBottom, float screenTop, const glm::mat4& projection, const glm::mat4& view) = 0;
    virtual ~Renderable() {}
};

#include "camera.h"
#include "text.h"

struct RenderItem {
    Renderable* object;
    float z;
    bool fixed;

    RenderItem(Renderable* obj, float zLayer, float isFixed) : object(obj), z(zLayer), fixed(isFixed) {}
};

class Renderer {
    private:

    const int TARGET_FPS = 60;
    const double FRAME_PERIOD = 1.0 / TARGET_FPS;

    GLFWwindow* window;
    Camera camera;

    glm::mat4 stdproj;
    glm::mat4 projection;
    glm::mat4 view;

    std::vector<RenderItem> renderQueue;

    public:

    float width, height;

    Renderer() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW\n";
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        width = videoMode->width;
        height = videoMode->height;

        window = glfwCreateWindow(width, height, "RTS", primaryMonitor, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            glfwTerminate();
            exit(-1);
        }

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
        glViewport(0, 0, width, height);

        glfwSetWindowUserPointer(window, &camera);
        glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
            Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            if (cam) cam->processScroll(yoffset);
        });

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void addObject(Renderable* obj, float zLayer = 0.0f, float isFixed = false) {
        renderQueue.emplace_back(obj, zLayer, isFixed);
    }    

    int render() {
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(window)) {
            auto frameStart = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = frameStart - lastTime;
            lastTime = frameStart;

            glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float screenLeft   = camera.position.x - width / camera.zoom * 2;
            float screenRight  = camera.position.x + width / camera.zoom * 2;
            float screenTop    = camera.position.y + height / camera.zoom * 2;
            float screenBottom = camera.position.y - height / camera.zoom * 2;

            view = glm::translate(glm::mat4(1.0f), -glm::vec3(camera.position, 0.0f));
            projection = glm::ortho(screenLeft, screenRight, screenBottom, screenTop);
            stdproj = glm::ortho(0.0f, width, 0.0f, height);

            std::sort(renderQueue.begin(), renderQueue.end(), [](const RenderItem& a, const RenderItem& b) {
                return a.z < b.z;
            });

            for (const auto& item : renderQueue) {
                item.object->render(screenLeft, screenRight, screenTop, screenBottom, item.fixed ? stdproj : projection, view);
            }            

            glfwSwapBuffers(window);
            glfwPollEvents();

            camera.processKeyboard(window, camera.speed, deltaTime.count());

            auto frameEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = frameEnd - frameStart;
            double sleepTime = FRAME_PERIOD - elapsed.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }
        }

        glfwTerminate();
        return 0;
    }
};
