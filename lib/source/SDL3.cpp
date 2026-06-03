#include "SDL3.hpp"

#include "Freetype.hpp"

#include <cmath>

//                      ---- Construction ----

sdl3::SDL3::SDL3()
{
    // Flags to init with.
    static constexpr SDL_InitFlags INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD;

    // Return if init fails.
    if (!SDL_Init(INIT_FLAGS)) { return; }

    // We're good?
    m_initialized = true;
}

sdl3::SDL3::~SDL3()
{
    // Quit SDL altogether now.
    SDL_Quit();
}

//                      ---- Public Functions ----

void sdl3::SDL3::pump_events() { SDL_PumpEvents(); }