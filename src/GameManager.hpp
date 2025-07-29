#pragma once

#include "Sound/Sound.hpp"
#include "TimeLimiter.hpp"
#include "GameLogic/SceneManagament/SceneManager.hpp"
#include "AnotherRendering/RenderSystem.hpp"
#include <chrono>

class Game {
    private:
    TimeLimiter timeLimiter;
    RenderSystem renderer;
    SceneManager sceneMgr;
    SoundManager soundMgr;
    bool isRunning = false;

    public:

    void init();
    void run();

    void update();
    void render();
};
