#include "LayerManager.hpp"

#include <algorithm>

void LayerManager::InitDefaultOrder() {
    layerOrder = {
        {RenderLayer::BACKGROUND, 0},
        {RenderLayer::TILEMAP, 1},
        {RenderLayer::ENTITIES, 2},
        {RenderLayer::PARTICLES, 3},
        {RenderLayer::UI, 4},
    };
}

int LayerManager::GetLayerOrder(RenderLayer layer) {
    return layerOrder[layer];
}

void LayerManager::SetLayerOrder(RenderLayer layer, int order) {
    layerOrder[layer] = order;
}

std::vector<RenderLayer> LayerManager::GetSortedLayers() const {
    std::vector<std::pair<RenderLayer, int>> layers(layerOrder.begin(), layerOrder.end());
    std::sort(layers.begin(), layers.end(), [](std::pair<RenderLayer, int>& a, std::pair<RenderLayer, int>& b) {
        return a.second < b.second;
    });

    std::vector<RenderLayer> sorted;
    for (const auto& pair : layers) {
        sorted.push_back(pair.first);
    }
    return sorted;
}

void LayerManager::DisableLayer(RenderLayer layer) {
    disabledLayers.insert(layer);
}

void LayerManager::EnableLayer(RenderLayer layer) {
    disabledLayers.erase(layer);
}

bool LayerManager::IsLayerEnabled(RenderLayer layer) const {
    return disabledLayers.find(layer) == disabledLayers.end();
}