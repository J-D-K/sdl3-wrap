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

const char *sdl3::Gamepad::get_name() const noexcept { return SDL_GetGamepadName(m_pad); }

SDL_JoystickID sdl3::Gamepad::get_id() const noexcept { return m_id; }

void sdl3::Gamepad::update() {}

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
