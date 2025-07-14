#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>
#include <iostream>

class Menu : public Renderable {
    public:
    
    void render(float x1, float x2, float y1, float y2, const glm::mat4& projection, const glm::mat4& view) override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, x2 - x1, 0, y2 - y1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};