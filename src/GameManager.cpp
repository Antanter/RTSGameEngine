#pragma once

#include "GameManager.hpp"
#include "Sound/sound.hpp"
#include "Rendering/render.hpp"
#include "GameLogic/SceneManagament/sceneLogic.hpp"
#include "GameLogic/InputAndController/InputHandler.hpp"
#include <chrono>
#include <thread>

void Game::init() {
}



void Game::run() {
    isRunning = true;

    using clock = std::chrono::high_resolution_clock;
    Renderer renderer(0, 0);
    auto prev = clock::now();

    while (isRunning) {
        auto now = clock::now();
        float deltaTime = std::chrono::duration<float>(now - prev).count();
        prev = now;

        InputHandler::pollEvents();
        renderer.renderFrame(deltaTime);
    }
}


void Game::shutdown() {}