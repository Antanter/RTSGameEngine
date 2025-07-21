#pragma once

#include "Sound/sound.hpp"
#include "GameLogic/SceneManagament/sceneLogic.hpp"
#include <chrono>

class Game {
    public:

    void init();
    void run();
    void shutdown();
    
    private:
    
    SceneManager sceneMgr;
    SoundManager soundMgr;
    bool isRunning = false;
    const int FPS = 60;
    const std::chrono::milliseconds frameDuration = std::chrono::milliseconds(1000 / FPS);
};
