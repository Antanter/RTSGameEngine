#pragma once

#include "tile.h"

#include <random>
#include <vector>
#include <GL/gl.h>

class Map {
    private:

    const int GRID_WIDTH = 1000;
    const int GRID_HEIGHT = 1000;
    const int TILE_SIZE = 75;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

    std::vector<Tile> grid;

    public:

    Map() : gen(rd()), dist(-100, 100) {
        grid.reserve(GRID_WIDTH * GRID_HEIGHT);
        for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
            grid.emplace_back(dist(gen) / 2000.0f);
        }
    }

    Tile getTile(int x, int y) { return grid.at(y * GRID_WIDTH + x); }

    void render(float screenLeft, float screenRight, float screenTop, float screenBottom) {
        int minX = std::max(0, int((screenLeft / TILE_SIZE) - 2));
        int maxX = std::min(GRID_WIDTH, int((screenRight / TILE_SIZE) + 2));
        int minY = std::max(0, int((screenTop / TILE_SIZE) - 2));
        int maxY = std::min(GRID_HEIGHT, int((screenBottom / TILE_SIZE) + 2));

        glPushMatrix(); // Сохраняем текущую матрицу

        // Повернуть карту
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Поворот вокруг Z на 45°

        // Сжать по вертикали
        glScalef(1.0f, 0.5f, 1.0f); // Сжатие по Y

        // Наклонить (если хочешь эффекта SimCity)
        glMultMatrixf(glm::value_ptr(glm::mat4(
            1.0f, -0.5f, 0.0f, 0.0f,
            0.0f, 1.0f,  0.0f, 0.0f,
            0.0f, 0.0f,  1.0f, 0.0f,
            0.0f, 0.0f,  0.0f, 1.0f
        )));

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                drawTile(x, y);
            }
        }

        glPopMatrix(); // Восстанавливаем матрицу
    }

    void drawTile(int x, int y) {
        Tile& tile = grid[y * GRID_WIDTH + x];
        
        float isoX = (x - y) * (TILE_SIZE / 2.0f);
        float isoY = (x + y) * (TILE_SIZE / 4.0f);

        float r, g, b;
        tile.getColor(r, g, b);
        glColor3f(r, g, b);

        glBegin(GL_QUADS);
            glVertex2f(isoX,                 isoY + TILE_SIZE / 2);
            glVertex2f(isoX + TILE_SIZE / 2, isoY);
            glVertex2f(isoX,                 isoY - TILE_SIZE / 2);
            glVertex2f(isoX - TILE_SIZE / 2, isoY);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(isoX,                 isoY + TILE_SIZE / 2);
            glVertex2f(isoX + TILE_SIZE / 2, isoY);
            glVertex2f(isoX,                 isoY - TILE_SIZE / 2);
            glVertex2f(isoX - TILE_SIZE / 2, isoY);
        glEnd();
    }
};