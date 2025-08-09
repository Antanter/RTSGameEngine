#pragma once

#include <chrono>
#include "Services.hpp"

class TimeLimiter : public IClock {
    private:
    float deltaTime = 0.f;
    const int targetFPS;
    std::chrono::high_resolution_clock::time_point frameStartTime;

    public:
    TimeLimiter(int targetFPS = 60);

    void BeginFrame();
    void EndFrame();
    float DeltaTime() const override { return deltaTime; }
};
    