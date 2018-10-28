#include "GameEngine.h"

void GameEngine::Init() {
    LOG_INFO("Engine", "Engine started!")
}

void GameEngine::Tick() {
    LOG_INFO("Engine", "Engine tick!")
}

void GameEngine::Close() {
    LOG_INFO("Engine", "Engine stop!")
}
