#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "camera.h"
#include "renderable.h"
#include "text.h"

class Renderer {
    private:

    const int TARGET_FPS = 60;
    const double FRAME_PERIOD = 1.0 / TARGET_FPS;
    
    Camera camera;

    std::vector<Renderable*> renderQueue;
    
    public:

    void addObject(Renderable* obj) {
        renderQueue.push_back(obj);
    }

    int render() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        GLFWwindow* window = glfwCreateWindow(
            videoMode->width, videoMode->height,
            "Fullscreen OpenGL Window",
            primaryMonitor, NULL);

        if (window == NULL) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return -1;
        }

        glViewport(0, 0, videoMode->width, videoMode->height);

        glfwSetWindowUserPointer(window, &camera);
        glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
            Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            if (cam) cam->processScroll(yoffset);
        });

        auto lastTime = std::chrono::high_resolution_clock::now();
        Text::getInstance().InitText(videoMode->width, videoMode->height);

        while (!glfwWindowShouldClose(window)) {
            auto frameStart = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = frameStart - lastTime;
            lastTime = frameStart;

            glClearColor(0.2f, 0.3f, 0.6f, 0.7f);
            glClear(GL_COLOR_BUFFER_BIT);

            float screenLeft   = camera.position.x - videoMode->width / camera.zoom * 2;
            float screenRight  = camera.position.x + videoMode->width / camera.zoom * 2;
            float screenTop    = camera.position.y - videoMode->height / camera.zoom * 2;
            float screenBottom = camera.position.y + videoMode->height / camera.zoom * 2;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(screenLeft, screenRight, screenTop, screenBottom, -1.0, 1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            for (Renderable* obj : renderQueue) {
                obj->render(screenLeft, screenRight, screenBottom, screenTop);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();

            camera.processKeyboard(window, camera.speed, deltaTime.count());

            auto frameEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = frameEnd - frameStart;
            double sleepTime = FRAME_PERIOD - elapsed.count();
            if (sleepTime > 0) std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
        }

        glfwTerminate();
        return 0;
    }
};
    