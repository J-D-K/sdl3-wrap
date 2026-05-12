#include "GamepadScanner.hpp"

//                          ---- Construction ----

sdl3::GamepadScanner::GamepadScanner()
{
    // Don't bother if this returns false.
    const bool hasPads = SDL_HasGamepad();
    if (!hasPads) { return; }

    // Get the list.
    m_joysticks = SDL_GetGamepads(&m_count);
    if (!m_joysticks) { return; }

    // We should be good if we made it here.
    m_initialized = true;
}

sdl3::GamepadScanner::~GamepadScanner()
{
    if (!m_joysticks) { return; }
    SDL_free(m_joysticks);
}

//                          ---- Public Functions ----

size_t sdl3::GamepadScanner::count() const noexcept { return m_count; }

SDL_JoystickID sdl3::GamepadScanner::at(size_t index) const noexcept
{
    if (index >= m_count) { return 0; }
    return m_joysticks[index];
}

const SDL_JoystickID *sdl3::GamepadScanner::begin() const noexcept
{
    static constexpr size_t BEGIN = 0;

    if (!m_joysticks) { return nullptr; }
    return &m_joysticks[BEGIN];
}

const SDL_JoystickID *sdl3::GamepadScanner::end() const noexcept
{
    if (!m_joysticks) { return nullptr; }
    return &m_joysticks[m_count];
}

//                          ---- Private Functions ----