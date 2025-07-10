#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "../GameLogic/map.h"
#include "../MenUI/menu.h"
#include "camera.h"

class Renderer {
private:
    const int TARGET_FPS = 60;
    const double FRAME_TIME = 1.0 / TARGET_FPS;

    Map map;
    Camera camera;
    Menu menuController;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

public:
    int render() {
        // ==== Инициализация GLFW и OpenGL ====
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

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
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwSetWindowUserPointer(window, &camera);
        glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
            Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            if (cam) cam->processScroll(yoffset);
        });

        auto lastTime = std::chrono::high_resolution_clock::now();

        // ==== Главный цикл ====
        while (!glfwWindowShouldClose(window)) {
            menuController.ProvoqueMenu(videoMode->width, videoMode->height);

            auto frameStart = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = frameStart - lastTime;
            lastTime = frameStart;

            // ==== Рендер ====
            glClearColor(0.2f, 0.3f, 0.6f, 0.8f);
            glClear(GL_COLOR_BUFFER_BIT);

            float screenLeft   = camera.position.x - videoMode->width / camera.zoom * 2;
            float screenRight  = camera.position.x + videoMode->width / camera.zoom * 2;
            float screenTop    = camera.position.y - videoMode->height / camera.zoom * 2;
            float screenBottom = camera.position.y + videoMode->height / camera.zoom * 2;

            // Настраиваем матрицу проекции и камеры
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(
                screenLeft,
                screenRight,
                screenTop,
                screenBottom,
                -1.0, 1.0
            );

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // Отрисовка карты
            map.render(screenLeft, screenRight, screenTop, screenBottom);

            glfwSwapBuffers(window);
            glfwPollEvents();

            camera.processKeyboard(window, camera.speed, deltaTime.count());

            // ==== Стабилизация FPS ====
            auto frameEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = frameEnd - frameStart;
            double sleepTime = FRAME_TIME - elapsed.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }
        }

        glfwTerminate();
        return 0;
    }
};