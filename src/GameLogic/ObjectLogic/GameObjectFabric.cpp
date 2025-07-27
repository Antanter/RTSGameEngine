#include "GameObjectFabric.hpp"

GameObjectBuilder::GameObjectBuilder() {
    obj = std::make_unique<GameObject>();
}