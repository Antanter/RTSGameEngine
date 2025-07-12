#include "Rendering/render.h"
#include "Rendering/text.h"
#include "GameLogic/map.h"
#include "MenUI/menu.h"

#include <iostream>
#include "glad.c"

int main() {
    Renderer renderer;

    Menu menu;
    Map map;

    renderer.addObject(&menu);
    renderer.addObject(&map);
    renderer.addObject(&Text::getInstance());

    return renderer.render();
}
