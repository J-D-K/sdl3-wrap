#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>
#include <string_view>

namespace sdl3
{
    class Window final : sdl3::CoreComponent
    {
        public:
            // No copying or moving.
            Window(const Window &)            = delete;
            Window(Window &&)                 = delete;
            Window &operator=(const Window &) = delete;
            Window &operator=(Window &&)      = delete;

            /// @brief Default.
            Window() = default;

            /// @brief Creates a new window.
            /// @param windowTitle Title of the window.
            /// @param windowWidth Width of the window.
            /// @param windowHeight Height of the window.
            Window(std::string_view windowTitle, int windowWidth, int windowHeight);

            /// @brief Destroys the window.
            ~Window();

            /// @brief Returns the width of the window.
            int get_width() const noexcept;

            /// @brief Returns the height of the window.
            int get_height() const noexcept;

            /// @brief Operator to act like a direct pointer to the underlying SDL_Window.
            operator SDL_Window *() const noexcept;

        private:
            /// @brief Stores the width of the window.
            int m_width{};

            /// @brief Stores the height of the window.
            int m_height{};

            /// @brief SDL Window.
            SDL_Window *m_window{};
    };
}