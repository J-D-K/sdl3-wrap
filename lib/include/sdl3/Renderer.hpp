#pragma once
#include "CoreComponent.hpp"
#include "Window.hpp"

namespace sdl3
{
    /// @brief Less headaches.
    class Texture;

    /// @brief Renderer wrapper class.
    class Renderer final : public sdl3::CoreComponent
    {
        public:
            // No copying or moving.
            Renderer(const Renderer &)            = delete;
            Renderer(Renderer &&)                 = delete;
            Renderer &operator=(const Renderer &) = delete;
            Renderer &operator=(Renderer &&)      = delete;

            /// @brief Default constructor.
            Renderer() = default;

            /// @brief Creates a new renderer instance. Calls create().
            /// @param window Window the renderer "belongs" to.
            Renderer(sdl3::Window &window) { Renderer::create(window); }

            /// @brief Destroys the renderer.
            ~Renderer()
            {
                if (!m_renderer) { return; }
                SDL_DestroyRenderer(m_renderer);
            }

            /// @brief Creates the render with the window passed.
            /// @param window Window to create renderer with.
            void create(sdl3::Window &window)
            {
                m_renderer = SDL_CreateRenderer(window.m_window, nullptr);
                if (!m_renderer) { return; }

                m_isInitialized = true;
            }

            /// @brief Sets the logical width and height of
            /// @param width
            /// @param height
            /// @return
            bool set_logical_width_height(int width, int height)
            {
                return SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_STRETCH);
            }

            /// @brief Clears the main render target to the color passed.
            /// @param clearColor Color to clear the target to.
            bool frame_begin(SDL_Color clearColor)
            {
                const bool setColor =
                    SDL_SetRenderDrawColor(m_renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
                if (!setColor) { return false; }

                return SDL_RenderClear(m_renderer);
            }

            /// @brief Presents render to screen.
            bool frame_end() { return SDL_RenderPresent(m_renderer); }

            /// @brief Renders a filled rectangle at the coordinates passed with the color passed.
            bool render_fill_rect(int x, int y, int width, int height, SDL_Color color)
            {
                // Set the draw color to the color passed.
                const bool drawColor = SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
                if (!drawColor) { return false; }

                // Rect.
                const SDL_FRect rect = {.x = static_cast<float>(x),
                                        .y = static_cast<float>(y),
                                        .w = static_cast<float>(width),
                                        .h = static_cast<float>(height)};

                return SDL_RenderFillRect(m_renderer, &rect);
            }

            /// @brief This allows the texture renderer to be set.
            friend class Texture;

        private:
            /// @brief Underlying SDL3 renderer.
            SDL_Renderer *m_renderer{};
    };
}