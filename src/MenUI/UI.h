#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "text.h"

class UI : public Renderable {
    private:

    std::string title;
    std::vector<Button> buttons;

    unsigned int VAO = 0, VBO = 0, shaderProgram = 0;

    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform mat4 projection;
        uniform mat4 model;

        void main() {
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec3 color;

        void main() {
            FragColor = vec4(color, 1.0);
        }
    )";

    void initShaders() {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "[UI] Vertex shader error: " << infoLog << "\n";
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "[UI] Fragment shader error: " << infoLog << "\n";
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "[UI] Shader program link error: " << infoLog << "\n";
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void initBuffers() {
        float quadVertices[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
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

    protected:

    void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color, const glm::mat4& projection) {
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glUniform3f(glGetUniformLocation(shaderProgram, "color"), color.r, color.g, color.b);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);
    }

    public:

    UI(std::string menuTitle = "Main Menu") : title(menuTitle) {
        initShaders();
        initBuffers();
    }

    void addButton(const std::string& label, glm::vec2 position, glm::vec2 size) {
        buttons.emplace_back(label, position, size);
    }

    void render(float x1, float x2, float y1, float y2, const glm::mat4& projection, const glm::mat4&) override {
        glm::mat4 orthoProj = glm::ortho(0.0f, x2 - x1, 0.0f, y2 - y1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glm::vec2 menuPos((x2 - x1) / 2.0f - 200.0f, (y2 - y1) / 2.0f - 150.0f);
        glm::vec2 menuSize(400.0f, 300.0f);
        drawQuad(menuPos, menuSize, glm::vec3(0.1f, 0.1f, 0.1f), orthoProj);

        for (Button& btn : buttons) {
            btn.render();
        }

        Text::getInstance().RenderText(
            title,
            menuPos.x + 20.0f,
            menuPos.y + menuSize.y - 40.0f,
            1.0f,
            glm::vec3(1.0f, 1.0f, 1.0f),
            orthoProj
        );

        glDisable(GL_BLEND);
    }
};

class UIElem {
    protected:

    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 color;

    UIElem(std::string text, glm::vec2 position, glm::vec3 color) : text(text), position(position), scale(scale), color(color) {}
};

class Label : public UI, public UIElem {
    private:

    std::string text;

    public:

    Label(std::string text, glm::vec2 position, float scale, glm::vec3 color)
     : text(text), position(position), scale(scale), color(color) {}

    void render(const glm::mat4& projection) override {
        Text::getInstance().RenderText(
            text,
            position.x,
            position.y,
            scale,
            color,
            projection
        );
    }
};

class Button : public UI {
    private:

    Label label;

    public:

    Button(Label lbl, glm::vec2 pos, glm::vec2 sz, glm::vec3 clr = glm::vec3(0.3f, 0.3f, 0.8f)) : label(lbl), position(pos), size(sz), color(clr) {}
    
    void render(const glm::mat4& projection) override {
        glm::vec2 btnPos = position;
        drawQuad(btnPos, size, color, projection);

        label.render(projection);
    }
};