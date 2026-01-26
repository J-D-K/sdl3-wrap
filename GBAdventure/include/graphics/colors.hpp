#pragma once
#include "sdl3.hpp"

namespace graphics::palette
{
    // This is a basic GB pallette I stole from voidsprite.
    inline constexpr SDL_Color LIGHT     = {.r = 0xC5, .g = 0xCA, .b = 0xA4, .a = 0xFF};
    inline constexpr SDL_Color MID_LIGHT = {.r = 0x8C, .g = 0x92, .b = 0x6B, .a = 0xFF};
    inline constexpr SDL_Color MID_DARK  = {.r = 0x4A, .g = 0x51, .b = 0x38, .a = 0xFF};
    inline constexpr SDL_Color DARK      = {.r = 0x18, .g = 0x18, .b = 0x18, .a = 0xFF};
}