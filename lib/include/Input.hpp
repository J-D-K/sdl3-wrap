#pragma once

#include <SDL3/SDL.h>
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

            /// @brief Enum for comparing key states to make this more console-like.
            enum class KeyStates : uint8_t
            {
                Idle     = 0,
                Pressed  = 1 << 1,
                Held     = 1 << 2,
                Released = 1 << 3
            };

            /// @brief Initializes input. We use a custom input to make it more console like and easier to read states.
            Input();

            /// @brief Updates the internal input data.
            void update() noexcept;

            /// @brief Returns the state for the scancode passed.
            /// @param scancode Key to get the state for.
            /// @return Const reference to the scan code.
            KeyStates get_key_state(SDL_Scancode scancode) const noexcept;

            /// @brief Returns the mouse button flags.
            SDL_MouseButtonFlags get_mouse_flags() const noexcept;

            /// @brief Returns the current X position of the mouse.
            float get_mouse_x() const noexcept;

            /// @brief Returns the current Y position of the mouse.
            float get_mouse_y() const noexcept;

        private:
            /// @brief Number of keys found in the initialization.
            int m_keyCount{};

            /// @brief Map for holding key states.
            std::unordered_map<SDL_Scancode, Input::KeyStates> m_keyMap{};

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