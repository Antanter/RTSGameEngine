#include "Rendering/render.hpp"
#include "Rendering/text.hpp"
#include "GameLogic/map.h"
#include "MenUI/menu.h"

#include <iostream>
#include "glad.c"

int main() {
    Renderer renderer;

    Menu menu;
    Text::getInstance().InitText();
    Map map;

    renderer.addObject(&menu, 1.5f, true);
    renderer.addObject(&Text::getInstance(), 1.0f, true);
    renderer.addObject(&map);

    return renderer.render();
}
