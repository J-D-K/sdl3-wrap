#include "SDL3.hpp"

#include "Freetype.hpp"

#include <cmath>

namespace
{
    /// @brief The flags used for initializing SDL.
    constexpr SDL_InitFlags SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD;
}

//                      ---- Construction ----

sdl3::SDL3::SDL3()
{
    if (!SDL_Init(SDL_INIT_FLAGS)) { return; }

    m_isInitialized = true;
}

sdl3::SDL3::~SDL3()
{
    // Quit SDL altogether now.
    SDL_Quit();
}

//                      ---- Public Functions ----

bool sdl3::SDL3::is_initialized() const noexcept { return m_isInitialized; }

void sdl3::SDL3::pump_events() { SDL_PumpEvents(); }