#pragma once
#include "SDL3.hpp"

// clang-format off
struct Input
{
    sdl3::Keyboard keyboard{};
    sdl3::Mouse mouse{};
    sdl3::GamepadManager gamepads{};
};
// clang-format on