#pragma once

#include "UI.h"
#include <vector>
#include <memory>

class UInterface {
    private:

    std::vector<std::shared_ptr<UIElem>> elements;

    public:

    UInterface() = default;

    template<typename T, typename... Args>
    void AddElem(Args&&... args) {
        static_assert(std::is_base_of<UIElem, T>::value, "T must inherit from UIElem");
        elements.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    void render(float screenLeft, float screenRight, float screenBottom, float screenTop, const glm::mat4& projection, const glm::mat4& view) {
        for (auto& elem : elements) {
            elem->render(screenLeft, screenRight, screenBottom, screenTop, projection, view);
        }
    }
};
