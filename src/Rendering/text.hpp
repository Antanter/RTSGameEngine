#pragma once

#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "render.hpp"
#include "shaders.hpp"

class Text : public Renderable {
    private:

    struct CharSeq {
        std::string text;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        CharSeq(const std::string& t, glm::vec2 p, glm::vec2 s, glm::vec3 c)
            : text(t), position(p), size(s), color(c) {}
    };
    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    void LoadShaders();
    void LoadFont(const std::string& fontPath, unsigned int fontSize);
    void LoadGlyphs();

    void RenderTextInternal(const CharSeq& seq, const glm::mat4& projection) const;
    void RenderTextInternal(const glm::mat4& viewjection, const std::string& text, glm::vec2 position, glm::vec2 size, glm::vec3 color) const;
    void RenderTextRaw(const std::string& text, float x, float y, glm::vec2 size, glm::vec3 color) const;

    FT_Library ft{};
    FT_Face face{};

    Shader* shader = nullptr;
    unsigned int VAO = 0;
    unsigned int VBO = 0;

    bool glyphsLoaded = false;
    std::map<char, Character> Characters;
    mutable std::vector<CharSeq> UI;
    
    public:
    
    Text(const std::string& fontPath, unsigned int fontSize = 48);
    ~Text();

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

    void render(const glm::mat4& viewjection) const override;
    void InitText();
    void AddLabel(const std::string& text, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
};
