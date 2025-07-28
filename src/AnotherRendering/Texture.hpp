#pragma once

#include <string>

class Texture {
    private:
    unsigned int id = 0;
    int width = 0;
    int height = 0;

    std::string filePath;

    void LoadFromFile(const std::string& path);

    public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(int slot = 0) const;
    void Unbind() const;

    int GetWidth() const;
    int GetHeight() const;
    unsigned int GetID() const;
};
