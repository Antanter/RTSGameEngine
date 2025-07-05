#include "tile.h"

class Map {
    private:

    const int GRID_WIDTH = 100;
    const int GRID_HEIGHT = 100;

    Tile* arr;

    Map() {
        arr = new Tile[GRID_WIDTH * GRID_HEIGHT];
        for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
            arr[i] = Tile();
        }
    }

    public:

    Tile getTile(int x, int y) { return arr[y * GRID_WIDTH + x]; }
};