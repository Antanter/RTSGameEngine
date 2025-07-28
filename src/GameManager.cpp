#include "GameManager.hpp"
#include "Sound/sound.hpp"
#include "Rendering/Render.hpp"
#include "GameLogic/SceneManagament/SceneManager.hpp"
#include "GameLogic/InputAndController/InputHandler.hpp"
#include <chrono>
#include <thread>

void Game::init() {
    soundMgr.init();
}

void Game::run() {
    isRunning = true;

    using clock = std::chrono::high_resolution_clock;
    Renderer renderer(0, 0);

    while (isRunning) {
        InputHandler::pollEvents();
        renderer.renderFrame();
    }
}