#include "Input.hpp"

#include <cmath>
#include <span>

//                      ---- Construction ----

//                      ---- Public Functions ----

void sdl3::Input::update() noexcept
{
    // Update mouse.
    SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    // Grab the array of key states from SDL.
    std::span<const bool> keystates{SDL_GetKeyboardState(nullptr), SDL_SCANCODE_COUNT};

    // Loop and update each state.
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) { Input::update_keystate(static_cast<SDL_Scancode>(i), keystates[i]); }

    // Same for mouse.
    for (int i = 0; i < MOUSE_BIT_COUNT; i++) { Input::update_mousestate(i, mouseFlags); }
}

sdl3::Input::State sdl3::Input::get_key_state(SDL_Scancode scancode) const noexcept { return m_keyArray.at(scancode); }

sdl3::Input::State sdl3::Input::get_mouse_button_state(Input::MouseButton button) const noexcept
{
    return m_mouseArray.at(static_cast<size_t>(button));
}

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

    // Update state.
    if (pressed) { keyState = State::Pressed; }
    else if (held) { keyState = State::Held; }
    else if (released) { keyState = State::Released; }
    else
    {
        keyState = State::Idle;
    }
}

void sdl3::Input::update_mousestate(int buttonIndex, SDL_MouseButtonFlags flags) noexcept
{
    // Reference to button state.
    Input::State &buttonState = m_mouseArray.at(buttonIndex);

    // Mask the button bit out.
    const bool buttonDown = flags >> (buttonIndex - 1) & 1;

    // Button conditions as above.
    const bool pressed  = buttonDown && buttonState != State::Pressed && buttonState != State::Held;
    const bool held     = buttonDown && (buttonState == State::Pressed || buttonState == State::Held);
    const bool released = !buttonDown && (buttonState == State::Pressed || buttonState == State::Held);

    // Update state.
    if (pressed) { buttonState = State::Pressed; }
    else if (held) { buttonState = State::Held; }
    else if (released) { buttonState = State::Released; }
    else
    {
        buttonState = State::Idle;
    }
}