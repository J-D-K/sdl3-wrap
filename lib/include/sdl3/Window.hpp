#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>
#include <string_view>

namespace sdl3
{
    /// @brief Prevents headaches later.
    class Renderer;

    /// @brief Window wrapper class.
    class Window final : public sdl3::CoreComponent
    {
        public:
            // No copying or moving.
            Window(const Window &)            = delete;
            Window(Window &&)                 = delete;
            Window &operator=(const Window &) = delete;
            Window &operator=(Window &&)      = delete;

            /// @brief Default constructor.
            Window() = default;

            /// @brief Constructor. Calls create() for you.
            Window(std::string_view title, int width, int height) { Window::create(title, width, height); }

            /// @brief Constructor Calls create()
            Window(std::string_view title, int width, int height, SDL_WindowFlags flags)
            {
                Window::create(title, width, height, flags);
            }

            /// @brief Destructor. Destroys the window.
            ~Window()
            {
                if (!m_window) { return; }

                SDL_DestroyWindow(m_window);
            }

            /// @brief Creates a new window.
            /// @param title Title of the window.
            /// @param width Width of the window.
            /// @param height Height of the window.
            void create(std::string_view title, int width, int height)
            {
                // Store these.
                m_width  = width;
                m_height = height;

                // Create the window.
                m_window = SDL_CreateWindow(title.data(), width, height, 0);
                if (!m_window) { return; }

                m_isInitialized = true;
            }

            /// @brief Creates the window and allows custom flags to be passed.
            /// @param flags Flags to pass to create().
            void create(std::string_view title, int width, int height, SDL_WindowFlags flags)
            {
                m_width  = width;
                m_height = height;

                m_window = SDL_CreateWindow(title.data(), width, height, flags);
                if (!m_window) { return; }

                m_isInitialized = true;
            }

            /// @brief Returns the width of the window.
            int get_width() const noexcept { return m_width; }

            /// @brief Returns the height of the window.
            int get_height() const noexcept { return m_height; }

            /// @brief Less headaches.
            friend class Renderer;

        private:
            /// @brief Width of the window.
            int m_width{};

            /// @brief Height of the window.
            int m_height{};

            /// @brief Window pointer.
            SDL_Window *m_window{};
    };
}