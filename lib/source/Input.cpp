#include "Input.hpp"

#include <span>

//                      ---- Construction ----

sdl3::Input::Input()
{
    // Start by getting the key count.
    SDL_GetKeyboardState(&m_keyCount);

    // Loop through and map them all.
    for (int i = 0; i < m_keyCount; i++)
    {
        m_keyMap.try_emplace(static_cast<SDL_Scancode>(i), static_cast<Input::KeyStates>(0));
    }
}

//                      ---- Public Functions ----

void sdl3::Input::update() noexcept
{
    // Update mouse.
    m_mouseFlags = SDL_GetMouseState(&m_mouseX, &m_mouseX);

    // Grab the array of key states from SDL.
    std::span<const bool> keystates{SDL_GetKeyboardState(nullptr), static_cast<size_t>(m_keyCount)};

    // Loop and update each state.
    for (int i = 0; i < m_keyCount; i++) { Input::update_keystate(static_cast<SDL_Scancode>(i), keystates[i]); }
}

sdl3::Input::KeyStates sdl3::Input::get_key_state(SDL_Scancode scancode) const noexcept
{
    // Attempt to locate the state first. If it doesn't exist, return 0.
    const auto findCode = m_keyMap.find(scancode);
    if (findCode == m_keyMap.end()) { return static_cast<Input::KeyStates>(0); }

    // Return the state.
    return findCode->second;
}

SDL_MouseButtonFlags sdl3::Input::get_mouse_flags() const noexcept { return m_mouseFlags; }

float sdl3::Input::get_mouse_x() const noexcept { return m_mouseX; }

float sdl3::Input::get_mouse_y() const noexcept { return m_mouseY; }

//                      ---- Private Functions ----

void sdl3::Input::update_keystate(SDL_Scancode scancode, bool state) noexcept
{
    // Try to find the scancode first.
    auto codeState = m_keyMap.find(scancode);
    if (codeState == m_keyMap.end()) { return; }

    // Grab the second.
    Input::KeyStates &keyState = codeState->second;

    // Conditions.
    const bool pressed  = state && keyState != KeyStates::Pressed && keyState != KeyStates::Held;
    const bool held     = state && (keyState == KeyStates::Pressed || keyState == KeyStates::Held);
    const bool released = !state && (keyState == KeyStates::Pressed || keyState == KeyStates::Held);

    if (pressed) { keyState = KeyStates::Pressed; }
    else if (held) { keyState = KeyStates::Held; }
    else if (released) { keyState = KeyStates::Released; }
    else
    {
        keyState = KeyStates::Idle;
    }
}