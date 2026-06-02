#include "Gamepad.hpp"

//                          ---- Constructor ----

sdl3::Gamepad::Gamepad(SDL_JoystickID joystick)
    : m_id{joystick}
    , m_pad{SDL_OpenGamepad(m_id)}
    , m_name{SDL_GetGamepadName(m_pad)}
{
    if (!m_pad) { return; }
    m_initialized = true;
}

sdl3::Gamepad::Gamepad(Gamepad &&gamepad)
    : m_id{gamepad.m_id}
    , m_pad{gamepad.m_pad}
    , m_name{gamepad.m_name}
{
    m_initialized = gamepad.m_initialized;

    gamepad.m_id          = 0;
    gamepad.m_pad         = nullptr;
    gamepad.m_initialized = false;
    gamepad.m_name        = nullptr;
}

sdl3::Gamepad::~Gamepad()
{
    if (!m_pad) { return; }
    SDL_CloseGamepad(m_pad);
}

//                          ---- Public Functions ----

const char *sdl3::Gamepad::get_name() const noexcept { return m_name; }

SDL_JoystickID sdl3::Gamepad::get_id() const noexcept { return m_id; }

bool sdl3::Gamepad::button_idle(SDL_GamepadButton button) const noexcept
{ return m_buttons[button] == sdl3::ButtonState::Idle; }

bool sdl3::Gamepad::button_pressed(SDL_GamepadButton button) const noexcept
{ return m_buttons[button] == sdl3::ButtonState::Pressed; }

bool sdl3::Gamepad::button_held(SDL_GamepadButton button) const noexcept
{ return m_buttons[button] == sdl3::ButtonState::Held; }

bool sdl3::Gamepad::button_released(SDL_GamepadButton button) const noexcept
{ return m_buttons[button] == sdl3::ButtonState::Released; }

void sdl3::Gamepad::update() { update_buttons(); }

sdl3::Gamepad &sdl3::Gamepad::operator=(Gamepad &&gamepad)
{
    m_initialized = gamepad.m_initialized;
    m_id          = gamepad.m_id;
    m_pad         = gamepad.m_pad;
    m_name        = gamepad.m_name;

    gamepad.m_initialized = false;
    gamepad.m_id          = 0;
    gamepad.m_pad         = nullptr;
    gamepad.m_name        = nullptr;

    return *this;
}

//                          ---- Private Functions ----

void sdl3::Gamepad::update_buttons()
{
    for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; i++)
    {
        // Get whether or not the button is down.
        sdl3::ButtonState &button = m_buttons[i];
        const bool buttonDown     = SDL_GetGamepadButton(m_pad, static_cast<SDL_GamepadButton>(i));

        // Update the state.
        const bool pressed  = buttonDown && button == sdl3::ButtonState::Idle;
        const bool held     = buttonDown && (button == sdl3::ButtonState::Pressed || button == sdl3::ButtonState::Held);
        const bool released = !buttonDown && (button == sdl3::ButtonState::Pressed || button == sdl3::ButtonState::Held);

        if (pressed) { button = sdl3::ButtonState::Pressed; }
        else if (held) { button = sdl3::ButtonState::Held; }
        else if (released) { button = sdl3::ButtonState::Released; }
        else
        {
            button = sdl3::ButtonState::Idle;
        }
    }
}
