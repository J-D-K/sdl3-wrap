#pragma once
#include "ButtonState.hpp"

#include <SDL3/SDL.h>
#include <array>

namespace sdl3
{
    /// @brief Keyboard input wrapper class.
    class Keyboard final
    {
        public:
            // No copying or moving.
            Keyboard(const Keyboard &)            = delete;
            Keyboard(Keyboard &&)                 = delete;
            Keyboard &operator=(const Keyboard &) = delete;
            Keyboard &operator=(Keyboard &&)      = delete;

            /// @brief Default.
            Keyboard() = default;

            /// @brief Updates the states of the keys.
            void update();

            /// @brief Returns whether or not the scancode passed returns no activity detected.
            /// @param scancode Scancode to check.
            bool idle(SDL_Scancode scancode) const noexcept;

            /// @brief Returns whether or not the scancode passed was pressed.
            /// @param scancode Scancode to check.
            bool pressed(SDL_Scancode scancode) const noexcept;

            /// @brief Returns whether or not the scancode passed was held.
            /// @param scancode Scancode to check.
            bool held(SDL_Scancode scancode) const noexcept;

            /// @brief Returns whether or not the scancode passed was released.
            /// @param scancode Scancode to check.
            bool released(SDL_Scancode scancode) const noexcept;

        private:
            /// @brief Create an array of states and initialize all to idle.
            std::array<sdl3::ButtonState, SDL_SCANCODE_COUNT> m_keys{sdl3::ButtonState::Idle};
    };
}