#pragma once

enum class RenderLayer {
    BACKGROUND,
    TILEMAP,
    ENTITIES,
    PARTICLES,
    UI,
};

class LayerManager {
    public:
    int GetLayerOrder(RenderLayer layer);
};
