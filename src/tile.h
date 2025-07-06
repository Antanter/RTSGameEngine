#pragma once

#include <random>

#include "TileType.hpp"

class Tile {
    private:

    float randBroun;
    TileType type = TileType::GROUND;
    TileOccp occupation = TileOccp::FREE;
    
    public:

    Tile(float broun) : randBroun(broun) {}

    TileType getType() const { return type; }
    void setType(TileType t) { type = t; }

    void getColor(float& r, float& g, float& b) const {
        switch (type) {
            case TileType::GROUND:
                r = 0.3f; g = 0.8f; b = 0.3f;
                break;
            case TileType::HOUSE:
                r = 0.7f; g = 0.2f; b = 0.2f;
                break;
            case TileType::ROAD:
                r = 0.5f; g = 0.5f; b = 0.5f;
                break;
            case TileType::WATER:
                r = 0.2f; g = 0.4f; b = 0.8f;
                break;
        }
        g += randBroun;
    }
};