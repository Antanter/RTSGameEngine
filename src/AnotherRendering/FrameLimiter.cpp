#include "FrameLimiter.hpp"
#include <thread>

using namespace std::chrono;

FrameLimiter::FrameLimiter(int targetFPS) : targetFPS(targetFPS) {}

void FrameLimiter::BeginFrame() {
    frameStartTime = high_resolution_clock::now();
}

void FrameLimiter::EndFrame() {
    auto frameEndTime = high_resolution_clock::now();
    auto frameDuration = duration_cast<microseconds>(frameEndTime - frameStartTime);

    deltaTime = frameDuration.count() / 1'000'000.0f;

    int targetFrameTimeMs = 1000 / targetFPS;
    int frameTimeMs = static_cast<int>(frameDuration.count() / 1000);

    if (frameTimeMs < targetFrameTimeMs) {
        int sleepTime = targetFrameTimeMs - frameTimeMs;
        std::this_thread::sleep_for(milliseconds(sleepTime));
    }
}

float FrameLimiter::GetDeltaTime() const {
    return deltaTime;
}