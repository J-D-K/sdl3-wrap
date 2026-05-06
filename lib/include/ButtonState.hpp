#pragma once
#include <cstdint>

namespace sdl3
{
    enum class ButtonState : uint8_t
    {
        Idle,
        Pressed,
        Held,
        Released
    };
}