#pragma once
#include <SDL3/SDL.h>
#include <string_view>

namespace sdl3
{
    class Window final
    {
        public:
            /// @brief Default.
            Window() = default;

            /// @brief Creates a new window.
            /// @param windowTitle Title of the window.
            /// @param windowWidth Width of the window.
            /// @param windowHeight Height of the window.
            Window(std::string_view windowTitle, int windowWidth, int windowHeight);

            /// @brief Destroys the window.
            ~Window();

            /// @brief Returns whether or not the window was created successfully.
            bool is_initialized() const noexcept;

            /// @brief Returns the width of the window.
            int get_width() const noexcept;

            /// @brief Returns the height of the window.
            int get_height() const noexcept;

            /// @brief Returns the renderer of the window.
            SDL_Renderer *get_renderer() const noexcept;

            /// @brief Sets the logical width and height of the window renderer.
            /// @param width Logical width.
            /// @param height Logical height.
            bool set_logical_render_dimensions(int width, int height);

        private:
            /// @brief Stores whether or not initialization was successful.
            bool m_isInitialized{};

            /// @brief Stores the width of the window.
            int m_width{};

            /// @brief Stores the height of the window.
            int m_height{};

            /// @brief Stores the logical width of the renderer.
            int m_logicalWidth{};

            /// @brief Stores the logical height of the renderer.
            int m_logicalHeight{};

            /// @brief SDL Window.
            SDL_Window *m_window{};

            /// @brief SDL Renderer.
            SDL_Renderer *m_renderer{};
    };
}