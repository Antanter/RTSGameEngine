#include "GameManager.hpp"
#include "Sound/Sound.hpp"
#include "GameLogic/SceneManagament/SceneManager.hpp"
#include "GameLogic/InputAndController/InputHandler.hpp"
#include <chrono>
#include <thread>

void Game::init() {
    renderer.Init();
    sceneMgr.Init();
    soundMgr.Init();
}

void Game::run() {
    init();
    while (true && !InputHandler::isKeyPressed(256)) update();
    shutdown();
}

void Game::shutdown() {
    renderer.ExitWindow();

    soundMgr.stopAll();
    sceneMgr.stopAll();

    glfwTerminate();
}

void Game::update() {
    timeLimiter.BeginFrame();

    InputHandler::pollEvents();

    sceneMgr.update();
    renderer.RenderFrame();

    timeLimiter.EndFrame();
}