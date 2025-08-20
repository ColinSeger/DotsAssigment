#pragma once
#include "glm/glm.hpp"

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};

enum class DebugDrawMode : uint8_t{
    None,
    Quad,
    Dots,
    Both
};
static const DebugDrawMode debugMode = DebugDrawMode::Quad;

const unsigned int DOT_AMOUNT = 20000;	

const float DOT_SIZE = 3;

const float DOT_VELOCITY = 50.0f;