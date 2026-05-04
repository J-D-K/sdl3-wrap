#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <cstdint>
#include <unordered_map>

namespace sdl3
{
    class Input final
    {
        public:
            /// @brief No copying or moving.
            Input(const Input &)            = delete;
            Input(Input &&)                 = delete;
            Input &operator=(const Input &) = delete;
            Input &operator=(Input &&)      = delete;

            /// @brief Initializes input. We use a custom input to make it more console like and easier to read states.
            Input() = default;

            /// @brief Updates the internal input data.
            void update() noexcept;

            /// @brief Returns whether or not the key passed is currently idle (no activity at all.)
            /// @param scancode Code to check.
            /// @return True if idle, false if not.
            bool key_idle(SDL_Scancode scancode) const noexcept;

            /// @brief Returns if the key passed was pressed on the given frame.
            /// @param scancode Code to check.
            /// @return True if pressed, false if not.
            bool key_pressed(SDL_Scancode scancode) const noexcept;

            /// @brief Returns whether or not the key passed is being held.
            /// @param scancode Scancode to check.
            /// @return True if held, false if not.
            bool key_held(SDL_Scancode scancode) const noexcept;

            /// @brief Returns if the key passed was released.
            /// @param scancode Scancode to check.
            /// @return True if released. False if not.
            bool key_released(SDL_Scancode scancode) const noexcept;

            /// @brief Returns the mouse button flags.
            SDL_MouseButtonFlags get_mouse_flags() const noexcept;

            /// @brief Returns the current X position of the mouse.
            float get_mouse_x() const noexcept;

            /// @brief Returns the current Y position of the mouse.
            float get_mouse_y() const noexcept;

        private:
            /// @brief Enum for comparing key states to make this more console-like.
            enum class State : uint8_t
            {
                Idle,
                Pressed,
                Held,
                Released
            };

            /// @brief Number of keys found in the initialization.
            int m_keyCount{};

            /// @brief Array of key states.
            std::array<Input::State, SDL_SCANCODE_COUNT> m_keyArray{State::Idle};

            /// @brief Stored mouse X.
            float m_mouseX{};

            /// @brief Stored mouse Y.
            float m_mouseY{};

            /// @brief Flags for mouse input. uint32_t.
            SDL_MouseButtonFlags m_mouseFlags{};

            /// @brief Updates the internal keystate with the state passed.
            /// @param scancode Scan code to update.
            /// @param state Current state of the key.
            void update_keystate(SDL_Scancode scancode, bool state) noexcept;
    };
}