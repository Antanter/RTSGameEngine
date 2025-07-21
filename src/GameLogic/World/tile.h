#pragma once

#include <random>

enum class TileType {
    GROUND,
    HOUSE,
    ROAD,
    WATER
};

enum class TileOccp {
    FREE,
    OCCUPIED
};

class Tile {
    private:

    float randBroun;
    TileType type = TileType::GROUND;
    TileOccp occupation = TileOccp::FREE;
    
    public:

    inline float clamp(float v, float min = 0.0f, float max = 1.0f) const {
        return (v < min) ? min : (v > max) ? max : v;
    }    

    Tile(float broun) : randBroun(broun) {}

    TileType getType() const { return type; }
    void setType(TileType t) { type = t; }

    void getColor(float& r, float& g, float& b) const {
        switch (type) {
            case TileType::GROUND:
                r = clamp(0.3f);
                g = clamp(0.8f + randBroun);
                b = clamp(0.3f);
                break;
            case TileType::HOUSE:
                r = clamp(0.7f + randBroun);
                g = clamp(0.2f + randBroun);
                b = clamp(0.2f + randBroun);
                break;
            case TileType::ROAD:
                r = clamp(0.5f + randBroun);
                g = clamp(0.5f + randBroun);
                b = clamp(0.5f + randBroun);
                break;
            case TileType::WATER:
                r = clamp(0.2f);
                g = clamp(0.4f);
                b = clamp(0.8f + randBroun);
                break;
        }
    }    
};