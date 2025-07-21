#pragma once

class Renderable {
    private:

    float zLayer;
    bool isFixed;

    public:

    virtual ~Renderable() = default;
    virtual void render(const glm::mat4& viewjection) const = 0;
    float getZ() const { return zLayer; };
    bool isFixed() const { return isFixed; };
};
