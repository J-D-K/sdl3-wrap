#pragma once
#include "ButtonState.hpp"

#include <SDL3/SDL.h>
#include <array>

namespace sdl3
{
    /// @brief Mouse input wrapper.
    class Mouse final
    {
        public:
            // No copying or moving.
            Mouse(const Mouse &)            = delete;
            Mouse(Mouse &&)                 = delete;
            Mouse &operator=(const Mouse &) = delete;
            Mouse &operator=(Mouse &&)      = delete;

            /// @brief Default.
            Mouse() = default;

            /// @brief Runs the update routine.
            void update();

            /// @brief Returns the current X coordinate of the mouse.
            float x() const noexcept;

            /// @brief Returns the current Y coordinate of the mouse.
            float y() const noexcept;

            /// @brief Returns the current global X of the mouse.
            float global_x() const noexcept;

            /// @brief Returns the current global Y of the mouse.
            float global_y() const noexcept;

            /// @brief Returns whether or not the button passed is idle.
            /// @param button Button to check.
            bool idle(uint32_t button) const noexcept;

            /// @brief Returns whether or not the button passed is pressed.
            /// @param button Button to check.
            bool pressed(uint32_t button) const noexcept;

            /// @brief Returns whether or not the button passed is being held.
            /// @param button Button to check.
            bool held(uint32_t button) const noexcept;

            /// @brief Returns whether or not the passed was released.
            /// @param button Button to check.
            bool released(uint32_t button) const noexcept;

        private:
            /// @brief Maximum number of mouse buttons.
            static constexpr size_t MOUSE_BUTTON_MAX = 32;

            /// @brief Stored X coordinate.
            float m_x{};

            /// @brief Stored Y coordinate.
            float m_y{};

            /// @brief Stored global X.
            float m_globalX{};

            /// @brief Stored global Y.
            float m_globalY{};

            /// @brief Stored button flags.
            SDL_MouseButtonFlags m_mouseFlags{};

            /// @brief Array of button states for the mouse buttons.
            std::array<sdl3::ButtonState, MOUSE_BUTTON_MAX> m_buttons{sdl3::ButtonState::Idle};
    };
}