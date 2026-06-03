#include "Timer.hpp"

#include <SDL3/SDL.h>

//                      ---- Construction ----

sdl3::Timer::Timer() noexcept
    : m_beginTicks{SDL_GetTicks()} {};

sdl3::Timer::Timer(uint64_t trigger) noexcept
    : m_beginTicks{SDL_GetTicks()}
    , m_triggerTicks{trigger} {};

//                      ---- Public Functions ----

void sdl3::Timer::reset() noexcept { m_beginTicks = SDL_GetTicks(); }

void sdl3::Timer::set_trigger(uint64_t trigger) noexcept { m_triggerTicks = trigger; }

bool sdl3::Timer::triggered() noexcept
{
    // Store this.
    const uint64_t ticks = SDL_GetTicks();

    // Trigger?
    const bool triggered = ticks - m_beginTicks >= m_triggerTicks;
    if (triggered) { m_beginTicks = ticks; }

    return triggered;
}

//                      ---- Private Functions ----