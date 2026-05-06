#include "Keyboard.hpp"

#include <span>

//                      ---- Construction ----

//                      ---- Public Functions ----

void sdl3::Keyboard::update()
{
    // Span the current codes.
    std::span<const bool> codeSpan{SDL_GetKeyboardState(nullptr), SDL_SCANCODE_COUNT};

    for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
    {
        // Grab the current state of the key and the corresponding state.
        const bool codeDown      = codeSpan[i];
        sdl3::ButtonState &state = m_keys[i];

        // Conditions.
        const bool pressed  = codeDown && state == sdl3::ButtonState::Idle;
        const bool held     = codeDown && (state == sdl3::ButtonState::Pressed || state == sdl3::ButtonState::Held);
        const bool released = !codeDown && (state == sdl3::ButtonState::Pressed || state == sdl3::ButtonState::Held);

        if (pressed) { state = sdl3::ButtonState::Pressed; }
        else if (held) { state = sdl3::ButtonState::Held; }
        else if (released) { state = sdl3::ButtonState::Released; }
        else
        {
            state = sdl3::ButtonState::Idle;
        }
    }
}

bool sdl3::Keyboard::idle(SDL_Scancode scancode) const noexcept { return m_keys[scancode] == sdl3::ButtonState::Idle; }

bool sdl3::Keyboard::pressed(SDL_Scancode scancode) const noexcept { return m_keys[scancode] == sdl3::ButtonState::Pressed; }

bool sdl3::Keyboard::held(SDL_Scancode scancode) const noexcept { return m_keys[scancode] == sdl3::ButtonState::Held; }

bool sdl3::Keyboard::released(SDL_Scancode scancode) const noexcept { return m_keys[scancode] == sdl3::ButtonState::Released; }

//                      ---- Private Functions ----