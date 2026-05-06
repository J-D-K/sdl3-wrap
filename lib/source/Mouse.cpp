#include "Mouse.hpp"

//                      ---- Construction ----

//                      ---- Public Functions ----

void sdl3::Mouse::update()
{
    // Update mouse state and X and Y coords.
    m_mouseFlags = SDL_GetMouseState(&m_x, &m_y);
    SDL_GetGlobalMouseState(&m_globalX, &m_globalY);

    // Loop and update button states.
    for (uint32_t i = 0; i < MOUSE_BUTTON_MAX; i++)
    {
        // Reference to the state.
        sdl3::ButtonState &state = m_buttons[i];

        // Whether or not the button is currently down.
        const bool down = m_mouseFlags & (1 << i) != 0;

        // Conditions.
        const bool pressed  = down && state == sdl3::ButtonState::Idle;
        const bool held     = down && (state == sdl3::ButtonState::Pressed || state == sdl3::ButtonState::Held);
        const bool released = !down && (state == sdl3::ButtonState::Pressed || state == sdl3::ButtonState::Held);

        // Update state.
        if (pressed) { state = sdl3::ButtonState::Pressed; }
        else if (held) { state = sdl3::ButtonState::Held; }
        else if (released) { state = sdl3::ButtonState::Released; }
        else
        {
            state = sdl3::ButtonState::Released;
        }
    }
}

float sdl3::Mouse::x() const noexcept { return m_x; }

float sdl3::Mouse::y() const noexcept { return m_y; }

float sdl3::Mouse::global_x() const noexcept { return m_globalX; }

float sdl3::Mouse::global_y() const noexcept { return m_globalY; }

bool sdl3::Mouse::idle(uint32_t button) const noexcept { return m_buttons[button] == sdl3::ButtonState::Idle; }

bool sdl3::Mouse::pressed(uint32_t button) const noexcept { return m_buttons[button] == sdl3::ButtonState::Pressed; }

bool sdl3::Mouse::held(uint32_t button) const noexcept { return m_buttons[button] == sdl3::ButtonState::Held; }

bool sdl3::Mouse::released(uint32_t button) const noexcept { return m_buttons[button] == sdl3::ButtonState::Released; }

//                      ---- Private Functions ----