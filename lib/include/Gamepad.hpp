#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>

namespace sdl3
{
    /// @brief Gamepad wrapper class.
    class Gamepad final : public sdl3::CoreComponent
    {
        public:
            // No copying.
            Gamepad(const Gamepad &)            = delete;
            Gamepad &operator=(const Gamepad &) = delete;

            /// @brief Constructor.
            Gamepad(SDL_JoystickID joystick);

            /// @brief Move constructor.
            Gamepad(Gamepad &&gamepad);

            /// @brief Destructor. Closes gamepad.
            ~Gamepad();

            /// @brief Returns the name of the gamepad.
            const char *get_name() const noexcept;

            /// @brief Returns the joystick Id of the Gamepad.
            SDL_JoystickID get_id() const noexcept;

            /// @brief Update routine. Updates internal SDL_Gamepad.
            void update();

            /// @brief Move operator.
            Gamepad &operator=(Gamepad &&gamepad);

        private:
            /// @brief ID.
            SDL_JoystickID m_id{};

            /// @brief Internally wrapped SDL_Gamepad.
            SDL_Gamepad *m_pad{};

            /// @brief Stores the pointer to the gamepad name.
            const char *m_name{};

            /// @brief Scans and stores the features the gamepad has.
            bool initialize_features();
    };
}