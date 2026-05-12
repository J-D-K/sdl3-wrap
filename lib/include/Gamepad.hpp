#pragma once
#include <SDL3/SDL.h>

namespace sdl3
{
    /// @brief Gamepad wrapper class.
    class Gamepad final
    {
        public:
            /// @brief Constructor.
            Gamepad(SDL_JoystickID joystick);

            /// @brief Destructor. Closes gamepad.
            ~Gamepad();

            /// @brief Update routine. Updates internal SDL_Gamepad.
            void update();

        private:
            /// @brief Internally wrapped SDL_Gamepad.
            SDL_Gamepad *m_pad{};
    };
}