#pragma once

#include <chrono>
#include <thread>

class FrameLimiter {
    private:
    const int targetFPS;
    std::chrono::high_resolution_clock::time_point frameStartTime;
    float deltaTime;

    public:
    FrameLimiter(int targetFPS = 60);

    void BeginFrame();
    void EndFrame();
    float GetDeltaTime() const;
};
    