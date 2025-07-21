#pragma once

#include "Sound/sound.hpp"
#include "Rendering/render.hpp"
#include "GameLogic/SceneManagament/sceneLogic.hpp"
#include <chrono>

class Game {
    private:
    
    SceneManager sceneMgr;
    SoundManager soundMgr;
    bool isRunning = false;
    const int FPS = 60;
    const std::chrono::milliseconds frameDuration = std::chrono::milliseconds(1000 / FPS);

    public:

    void init();
    void run();
    void shutdown();
};
