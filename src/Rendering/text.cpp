#include "text.hpp"
#include <glad/glad.h>
#include <iostream>
#include <algorithm>

Text::Text(const std::string& fontPath, unsigned int fontSize) {
    LoadShaders();
    LoadFont(fontPath, fontSize);
    LoadGlyphs();
}

Text::~Text() {
    for (auto& kv : Characters)
        glDeleteTextures(1, &kv.second.TextureID);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    delete shader;
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Text::InitText() {
    shader->use();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text::LoadShaders() {
    shader = new Shader("shaders/text.vs", "shaders/text.fs");
}

void Text::LoadFont(const std::string& fontPath, unsigned int fontSize) {
    if (FT_Init_FreeType(&ft))
        std::cerr << "Failed to init FreeType" << std::endl;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cerr << "Failed to load font: " << fontPath << std::endl;
    FT_Set_Pixel_Sizes(face, 0, fontSize);
}

void Text::LoadGlyphs() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for (unsigned char c = 0; c < 128; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;
        unsigned int tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character ch{
            tex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert({static_cast<char>(c), ch});
    }
    glyphsLoaded = true;
}

void Text::AddLabel(const std::string& text, glm::vec2 position,
                    glm::vec2 size, glm::vec3 color) {
    UI.emplace_back(text, position, size, color);
}

void Text::render(float, float, float, float,
                  const glm::mat4& projection, const glm::mat4&) {
    shader->use();
    shader->setUniform("text", 0);
    for (const auto& seq : UI)
        RenderTextInternal(seq, projection);
    UI.clear();
}

void Text::RenderTextInternal(const CharSeq& seq, const glm::mat4& projection) {
    RenderTextInternal(seq.text, seq.position, seq.size, seq.color, projection);
}

void Text::RenderTextInternal(std::string text, glm::vec2 position,
                              glm::vec2 size, glm::vec3 color,
                              const glm::mat4& projection) {
    shader->setUniform("projection", projection);
    shader->setUniform("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    const float outline = 1.0f;
    glm::vec3 outlineColor(0.0f);
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            if (dx != 0 || dy != 0)
                RenderTextRaw(text, position.x + dx * outline,
                              position.y + dy * outline, size, outlineColor);

    RenderTextRaw(text, position.x, position.y, size, color);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::RenderTextRaw(const std::string& text, float x, float y,
                         glm::vec2 size, glm::vec3 color) {
    shader->setUniform("textColor", color);
    std::vector<std::string> lines;
    std::string line, word;
    float lineW = 0;
    auto getWidth = [&](const std::string& s){
        float w = 0;
        for (char c : s)
            w += (Characters[c].Advance >> 6);
        return w;
    };

    for (char c : text) {
        if (c == ' ' || c == '\n') {
            if (lineW + getWidth(word + (c == ' ' ? " " : "")) > size.x) {
                lines.push_back(line);
                line = word + (c == ' ' ? " " : "");
                lineW = getWidth(line);
            } else {
                line += word + (c == ' ' ? " " : "");
                lineW += getWidth(word + (c == ' ' ? " " : ""));
            }
            word.clear();
            if (c == '\n') {
                lines.push_back(line);
                line.clear();
                lineW = 0;
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        if (lineW + getWidth(word) > size.x) {
            lines.push_back(line);
            line = word;
        } else {
            line += word;
        }
    }
    if (!line.empty()) lines.push_back(line);

    float maxH = 0;
    for (char c : text)
        maxH = std::max(maxH, static_cast<float>(Characters[c].Size.y));
    float totalH = lines.size() * maxH;
    float scale = size.y / totalH;
    float startY = y + size.y - maxH * scale;

    for (const auto& ln : lines) {
        float w = getWidth(ln) * scale;
        float startX = x + (size.x - w) / 2;
        float cx = startX;
        for (char c : ln) {
            const auto& ch = Characters.at(c);
            float xpos = cx + ch.Bearing.x * scale;
            float ypos = startY - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            float verts[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            cx += (ch.Advance >> 6) * scale;
        }
        startY -= maxH * scale;
    }
}