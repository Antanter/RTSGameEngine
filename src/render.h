#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>
#include <iostream>

class Renderer {
    private:

    const int TARGET_FPS = 60;
    const double FRAME_TIME = 1.0 / TARGET_FPS;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    public:

    int render() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Get the primary monitor
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        // Create a fullscreen window on the primary monitor
        GLFWwindow* window = glfwCreateWindow(
            videoMode->width, videoMode->height,
            "Fullscreen OpenGL Window",
            primaryMonitor, // <- Fullscreen
            NULL);

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

        // Set viewport and callback
        glViewport(0, 0, videoMode->width, videoMode->height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Game/render loop
        while (!glfwWindowShouldClose(window)) {
            auto frameStart = std::chrono::high_resolution_clock::now();

            // ==== Render ====
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
            // ================

            // ==== Reduce FPS ====
            auto frameEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = frameEnd - frameStart;

            double sleepTime = FRAME_TIME - elapsed.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }
            // =========================
        }

        glfwTerminate();
        return 0;
    }
};