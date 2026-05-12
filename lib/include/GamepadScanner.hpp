#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>
#include <cstddef>

namespace sdl3
{
    /// @brief This is a wrapped scanner class for Gamepads for RAII.
    class GamepadScanner final : public sdl3::CoreComponent
    {
        public:
            /// @brief Constructor. Calls SDL_GetGamepads and stores the array locally.
            GamepadScanner();

            /// @brief Destructor. Frees the array.
            ~GamepadScanner();

            /// @brief Returns the number of gamepads found.
            size_t count() const noexcept;

            /// @brief Returns the joystick ID at the index passed. 0 if none exist or index it out of range.
            /// @param index Index of the joystick id to get.
            SDL_JoystickID at(size_t index) const noexcept;

            /// @brief Begin. For range based for loops.
            const SDL_JoystickID *begin() const noexcept;

            /// @brief End. For range based for loops.
            const SDL_JoystickID *end() const noexcept;

        private:
            /// @brief Array of joystick IDs.
            SDL_JoystickID *m_joysticks{};

            /// @brief Number of joysticks found.
            int m_count{};
    };
}