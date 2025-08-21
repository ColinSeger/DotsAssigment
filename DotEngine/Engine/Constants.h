#pragma once
#include "glm/glm.hpp"

constexpr uint16_t SCREEN_WIDTH = 1920;
constexpr uint16_t SCREEN_HEIGHT = 1080;
constexpr glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};

enum class DebugDrawMode : uint8_t{
    None,
    Quad,
    Dots,
    Both
};
constexpr DebugDrawMode debugMode = DebugDrawMode::None;

constexpr unsigned int DOT_AMOUNT = 45000;	

constexpr float DOT_SIZE = 3;

constexpr float DOT_VELOCITY = 50.0f;