#pragma once

#include <chrono>

class TimeLimiter {
    private:
    const int targetFPS;
    std::chrono::high_resolution_clock::time_point frameStartTime;
    float deltaTime;

    public:
    TimeLimiter(int targetFPS = 60);

    void BeginFrame();
    void EndFrame();
    float GetDeltaTime() const;
};
    