#pragma once

#include "Sound/sound.hpp"
#include "Rendering/Render.hpp"
#include "GameLogic/SceneManagament/SceneManager.hpp"
#include <chrono>

class Game {
    private:
    
    SceneManager sceneMgr;
    SoundManager soundMgr;
    bool isRunning = false;

    public:

    void init();
    void run();
};
