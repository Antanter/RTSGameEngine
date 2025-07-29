#include "GameManager.hpp"
#include "Sound/Sound.hpp"
#include "GameLogic/SceneManagament/SceneManager.hpp"
#include "GameLogic/InputAndController/InputHandler.hpp"
#include <chrono>
#include <thread>

void Game::init() {

}

void Game::run() {
    isRunning = true;

    while (isRunning) {
        timeLimiter.BeginFrame();
        InputHandler::pollEvents();
        update();
        render();
        timeLimiter.EndFrame();
    }
}

void Game::update() {
    float dt = timeLimiter.GetDeltaTime();
    sceneMgr.update(sceneMgr.getScene()->getName());

}

void Game::render() {
    for (const auto& obj : sceneMgr.getScene()->getRenderables()) {
        draw(obj);
    }
}
