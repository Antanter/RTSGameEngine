#include "Rendering/render.h"
#include "GameLogic/map.h"
#include "MenUI/menu.h"
#include <iostream>

int main() {
    Renderer renderer;

    Menu menu;
    renderer.addObject(&menu);

    return renderer.render();
}
