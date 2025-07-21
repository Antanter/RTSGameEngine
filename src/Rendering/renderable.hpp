#pragma once

class Renderable {
    private:

    float zLayer;
    bool isFixed;

    public:

    virtual ~Renderable() = default;
    virtual void render() const = 0;
    float getZ() const { return zLayer; };
    bool isFixed() const { return isFixed; };
};
