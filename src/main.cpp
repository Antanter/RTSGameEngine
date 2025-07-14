#include "Rendering/render.h"
#include "Rendering/text.h"
#include "GameLogic/map.h"
#include "MenUI/menu.h"

#include <iostream>
#include "glad.c"

int main() {
    Renderer renderer;

    //Menu menu;
    Text::getInstance().InitText();
    Map map;

    //renderer.addObject(&menu);
    renderer.addObject(&Text::getInstance(), 1.0f, true);
    renderer.addObject(&map);

    return renderer.render();
}
