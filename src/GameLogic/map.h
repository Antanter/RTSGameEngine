#pragma once

#include "tile.h"

#include <random>
#include <vector>
#include <GL/gl.h>

class Map {
    private:

    const int GRID_WIDTH = 1000;
    const int GRID_HEIGHT = 1000;
    const int TILE_SIZE = 150;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

    std::vector<Tile> grid;
    //std::chrono::steady_clock::time_point start;

    public:

    Map() : gen(rd()), dist(-100, 100) {
        //start = std::chrono::steady_clock::now();
        grid.reserve(GRID_WIDTH * GRID_HEIGHT);
        for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
            grid.emplace_back(dist(gen) / 2000.0f);
        }
    }

    Tile getTile(int x, int y) { return grid.at(y * GRID_WIDTH + x); }

    void render(float screenLeft, float screenRight, float screenTop, float screenBottom) {
        int minX = std::max(0, int((screenLeft / (TILE_SIZE * 0.33f))));
        int maxX = std::min(GRID_WIDTH, int(screenRight / (TILE_SIZE * 0.33f)));
        int minY = std::max(0, int((screenTop / (TILE_SIZE * 0.33f))));
        int maxY = std::min(GRID_HEIGHT, int(screenBottom / (TILE_SIZE * 0.33f)));
    
        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                drawTile(x, y);
            }
        }
    }
    
    void drawTile(int x, int y) {
        Tile& tile = grid[y * GRID_WIDTH + x];
    
        float isoX = (x - y) * (TILE_SIZE * 0.75f);
        float isoY = (x + y) * (TILE_SIZE * 0.33f);
    
        float r, g, b;
        tile.getColor(r, g, b);
        glColor3f(r, g, b);
    
        glPushMatrix();
        glTranslatef(isoX, isoY, 0.0f);
        glScalef(1.0f, 0.5f, 1.0f);
        
        //auto now = std::chrono::system_clock::now();

        glTranslatef(TILE_SIZE / 2, TILE_SIZE / 2, 0.0f);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(-TILE_SIZE / 2, -TILE_SIZE / 2, 0.0f);

        glBegin(GL_QUADS);
            glVertex2f(0, TILE_SIZE / 2);
            glVertex2f(TILE_SIZE, TILE_SIZE / 2);
            glVertex2f(TILE_SIZE, -TILE_SIZE / 2);
            glVertex2f(0, -TILE_SIZE / 2);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, TILE_SIZE / 2);
            glVertex2f(TILE_SIZE, TILE_SIZE / 2);
            glVertex2f(TILE_SIZE, -TILE_SIZE / 2);
            glVertex2f(0, -TILE_SIZE / 2);
        glEnd();
    
        glPopMatrix();
    }    
};