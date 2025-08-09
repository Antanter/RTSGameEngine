#pragma once

#include <vector>
#include <map>
#include <set>

enum class RenderLayer {
    BACKGROUND,
    TILEMAP,
    ENTITIES,
    PARTICLES,
    UI,
};

class LayerManager {
    private:
    std::map<RenderLayer, int> layerOrder;
    std::set<RenderLayer> disabledLayers;

    public:
    void InitDefaultOrder();

    int GetLayerOrder(RenderLayer layer);
    void SetLayerOrder(RenderLayer layer, int order);

    std::vector<RenderLayer> GetSortedLayers() const;

    void DisableLayer(RenderLayer layer);
    void EnableLayer(RenderLayer layer);
    bool IsLayerEnabled(RenderLayer layer) const;
};
