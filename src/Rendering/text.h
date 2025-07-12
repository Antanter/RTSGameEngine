#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

class Label {
    public:

    std::string text;
    float x;
    float y;
    float scale; 
    glm::vec3 color;

    Label(std::string text, float x, float y, float scale, glm::vec3 color)
        : text(text), x(x), y(y), scale(scale), color(color) {}
};

class Text : public Renderable {
    private:

    FT_Face face;
    FT_Library ft;

    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
    out vec2 TexCoords;
    
    uniform mat4 projection;
    
    void main() {
        gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
        TexCoords = vertex.zw;
    }
    )";
    
    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 FragColor;
    
    uniform sampler2D text;
    uniform vec3 textColor;
    
    void main() {
        float alpha = texture(text, TexCoords).r;
        FragColor = vec4(textColor, alpha);
    }
    )";

    unsigned int VAO, VBO, shaderProgram;

    bool shadersInitialized = false;
    bool encodingInitialized = false;
    bool glyphsLoaded = false;

    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    std::vector<Label> UI;
    std::map<char, Character> Characters;
    glm::mat4 projection;

    Text() {}
    Text(const Text&) = delete;
    void operator=(const Text&) = delete;

    public:

    static Text& getInstance() {
        static Text instance;
        return instance;
    }

    Text(float screenWidth, float screenHeight) { InitText(screenWidth, screenHeight); }

    void InitShaders() {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shadersInitialized = true;
    }

    void DownloadEncoding() {
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "Failed to init FreeType\n";
        }

        if (FT_New_Face(ft, "arial.ttf", 0, &face)) {
            std::cerr << "Failed to load font\n";
        }
        FT_Set_Pixel_Sizes(face, 0, 48);

        encodingInitialized = true;
    }

    void DownloadGlyphs() {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load Glyph\n";
                continue;
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        glyphsLoaded = true;
    }

    void RenderText(Label label) { RenderText(label.text, label.x, label.y, label.scale, label.color); }

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
        glUseProgram(shaderProgram);
        glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for (char c : text) {
            Character ch = Characters[c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.Advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void InitText(float screenWidth, float screenHeight) {
        InitShaders();
        DownloadEncoding();
        DownloadGlyphs();

        projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);
    }

    void AddLabel(std::string text, float x, float y, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)) {
        UI.push_back(Label(text, x, y, scale, color));
    }

    void render(float screenLeft, float screenRight, float screenTop, float screenBottom) override {
        for (Label label : UI) {
            if (screenLeft <= label.x <= screenRight && screenBottom <= label.y <= screenTop) {
                RenderText(label);
            }
        }
    }
};
