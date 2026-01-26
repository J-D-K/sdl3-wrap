#pragma once
#include "sdl3.hpp"

namespace ui::colors
{
    inline constexpr SDL_Color BLACK      = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
    inline constexpr SDL_Color WHITE      = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
    inline constexpr SDL_Color CLEAR      = {.r = 0x3D, .g = 0x3D, .b = 0x3D, .a = 0xFF};
    inline constexpr SDL_Color MENU       = {.r = 0xDD, .g = 0xDD, .b = 0xDD, .a = 0xFF};
    inline constexpr SDL_Color MENU_HOVER = {.r = 0xAA, .g = 0xAA, .b = 0xAA, .a = 0xFF};
}