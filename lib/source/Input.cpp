#include "Input.hpp"

#include <cmath>
#include <span>

//                      ---- Construction ----

//                      ---- Public Functions ----

void sdl3::Input::update() noexcept
{
    // Update mouse.
    m_mouseFlags = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    // Grab the array of key states from SDL.
    std::span<const bool> keystates{SDL_GetKeyboardState(nullptr), SDL_SCANCODE_COUNT};

    // Loop and update each state.
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) { Input::update_keystate(static_cast<SDL_Scancode>(i), keystates[i]); }
}

sdl3::Input::State sdl3::Input::get_key_state(SDL_Scancode scancode) const noexcept
{
    // Return the state.
    return m_keyArray.at(scancode);
}

SDL_MouseButtonFlags sdl3::Input::get_mouse_flags() const noexcept { return m_mouseFlags; }

int sdl3::Input::get_mouse_x() const noexcept { return std::round(m_mouseX); }

int sdl3::Input::get_mouse_y() const noexcept { return std::round(m_mouseY); }

//                      ---- Private Functions ----

void sdl3::Input::update_keystate(SDL_Scancode scancode, bool state) noexcept
{
    // Reference to keystate.
    Input::State &keyState = m_keyArray.at(scancode);

    // Conditions.
    const bool pressed  = state && keyState != State::Pressed && keyState != State::Held;
    const bool held     = state && (keyState == State::Pressed || keyState == State::Held);
    const bool released = !state && (keyState == State::Pressed || keyState == State::Held);

    if (pressed) { keyState = State::Pressed; }
    else if (held) { keyState = State::Held; }
    else if (released) { keyState = State::Released; }
    else
    {
        keyState = State::Idle;
    }
}