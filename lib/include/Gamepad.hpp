#pragma once
#include "ButtonState.hpp"
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>
#include <array>

namespace sdl3
{
    /// @brief Gamepad wrapper class.
    class Gamepad : public sdl3::CoreComponent
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

            /// @brief Returns whether or not the button passed is idle.
            /// @param button Button to check.
            /// @return True or false.
            bool button_idle(SDL_GamepadButton button) const noexcept;

            /// @brief Returns whether or not the button passed is pressed.
            /// @param button Button to check.
            /// @return True or false.
            bool button_pressed(SDL_GamepadButton button) const noexcept;

            /// @brief Returns whether or not the button passed is held.
            /// @param button Button to check.
            /// @return True or false.
            bool button_held(SDL_GamepadButton button) const noexcept;

            /// @brief Returns whether or not the button passed was released.
            /// @param button Button to check.
            /// @return True or false.
            bool button_released(SDL_GamepadButton button) const noexcept;

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

            /// @brief Array of buttons.
            std::array<sdl3::ButtonState, SDL_GAMEPAD_BUTTON_COUNT> m_buttons{};

            /// @brief Scans and stores the features the gamepad has.
            bool initialize_features();

            /// @brief
            void update_buttons();
    };
}