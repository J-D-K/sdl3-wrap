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

            /// @brief Default constructor. Nothing needs manual initialization.
            Input() = default;

            /// @brief Enum for comparing key states to make this more console-like.
            enum class State : uint8_t
            {
                Idle,
                Pressed,
                Held,
                Released
            };

            /// @brief Enum for mouse buttons.
            enum class MouseButton : uint32_t
            {
                Left   = 1,
                Middle = 2,
                Right  = 3
            };

            /// @brief Updates the internal input data.
            void update() noexcept;

            /// @brief Returns the state for the scancode passed.
            /// @param scancode Key to get the state for.
            /// @return Const reference to the scan code.
            State get_key_state(SDL_Scancode scancode) const noexcept;

            /// @brief Returns the current state of the button index passed.
            State get_mouse_button_state(MouseButton button) const noexcept;

            /// @brief Returns the current X position of the mouse.
            int get_mouse_x() const noexcept;

            /// @brief Returns the current Y position of the mouse.
            int get_mouse_y() const noexcept;

        private:
            /// @brief This is the number of mouse buttons SDL lets us detect in the bit mask.
            static constexpr size_t MOUSE_BIT_COUNT = 32;

            /// @brief Array of key states.
            std::array<Input::State, SDL_SCANCODE_COUNT> m_keyArray{State::Idle};

            /// @brief Array of mouse button states.
            std::array<Input::State, MOUSE_BIT_COUNT> m_mouseArray{State::Idle};

            /// @brief Stored mouse X.
            float m_mouseX{};

            /// @brief Stored mouse Y.
            float m_mouseY{};

            /// @brief Updates the internal keystate with the state passed.
            /// @param scancode Scan code to update.
            /// @param state Current state of the key.
            void update_keystate(SDL_Scancode scancode, bool state) noexcept;

            /// @brief Updates the current mouse button flags.
            /// @param buttonIndex Index of the button to update.
            /// @param flags Flags to check.
            void update_mousestate(int buttonIndex, SDL_MouseButtonFlags flags) noexcept;
    };
}