#pragma once

#include "UInterface.h"
#include <vector>
#include <memory>

class Menu : public Renderable {
    private:
    
    UInterface screen;

    public:

    Menu() {
        screen.AddElem<Button>("I wanna fuck it hardly", glm::vec2(25.0f, 25.0f), glm::vec2(100.0f, 100.0f));
    }

    void render(float screenLeft, float screenRight, float screenBottom, float screenTop, const glm::mat4& projection, const glm::mat4& view) override {
        screen.render(screenLeft, screenRight, screenBottom, screenTop, projection, view);
    }
};