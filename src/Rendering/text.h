#pragma once

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "renderable.h"
#include "label.h"

class Text : public Renderable {
private:
    Text();
    Text(const Text&) = delete;
    void operator=(const Text&) = delete;

    FT_Face face;
    FT_Library ft;

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

    const char* vertexShaderSource;
    const char* fragmentShaderSource;

public:
    static Text& getInstance();

    void InitText(float screenWidth, float screenHeight);
    void AddLabel(std::string text, float x, float y, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f));
    void RenderText(Label label);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

    void render(float screenLeft, float screenRight, float screenTop, float screenBottom) override;

private:
    void InitShaders();
    void DownloadEncoding();
    void DownloadGlyphs();
};
