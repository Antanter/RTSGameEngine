#pragma once

#include "tile.h"
#include <random>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Map : public Renderable {
    private:

    const int GRID_WIDTH = 1000;
    const int GRID_HEIGHT = 1000;
    const float TILE_SIZE = 1500.0f;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

    std::vector<Tile> grid;

    unsigned int VAO = 0, VBO = 0;
    unsigned int shaderProgram = 0;

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;

        void main() {
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec3 color;

        void main() {
            FragColor = vec4(color, 1.0);
        }
    )";

    void InitShaders() {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "ERROR: Vertex shader compilation failed\n" << infoLog << "\n";
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "ERROR: Fragment shader compilation failed\n" << infoLog << "\n";
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "ERROR: Shader program linking failed\n" << infoLog << "\n";
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void InitBuffers() {
        float quadVertices[] = {
            0.0f,        0.0f,
            TILE_SIZE,   0.0f,
            TILE_SIZE,   TILE_SIZE,
            0.0f,        TILE_SIZE
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    public:

    Map() : gen(rd()), dist(-100, 100) {
        InitShaders();
        InitBuffers();

        std::cerr << "[Map] Initialization complete.\n";

        grid.reserve(GRID_WIDTH * GRID_HEIGHT);
        for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
            grid.emplace_back(dist(gen) / 500.0f);
        }
    }

    void drawTile(int x, int y) {
        Tile& tile = grid[y * GRID_WIDTH + x];

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x * TILE_SIZE, y * TILE_SIZE, 0.0f));
        model = glm::translate(model, glm::vec3(TILE_SIZE / 2, TILE_SIZE / 2, 0.0f));
        model = glm::translate(model, glm::vec3(-TILE_SIZE / 2, -TILE_SIZE / 2, 0.0f));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        float r, g, b;
        tile.getColor(r, g, b);
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), r, g, b);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    void render(float screenLeft, float screenRight, float screenBottom, float screenTop, const glm::mat4& projection, const glm::mat4& view) override {
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection") , 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(VAO);

        int minX = std::max(0, int(screenLeft / TILE_SIZE));
        int maxX = std::max(0, std::min(GRID_WIDTH, int(screenRight / TILE_SIZE) + 1));
        int minY = std::max(0, int(screenTop / TILE_SIZE));
        int maxY = std::max(0, std::min(GRID_HEIGHT, int(screenBottom / TILE_SIZE) + 1));

        char buffer[256];
        sprintf(buffer, "minX: %d, maxX: %d.\n minY: %d, maxY: %d", minX, maxX, minY, maxY);
        Text::getInstance().AddLabel(buffer, 25.0f, 25.0f);

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                drawTile(x, y);
            }
        }

        glBindVertexArray(0);
        glUseProgram(0);
    }
};
