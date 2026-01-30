#pragma once
#include "CoreComponent.hpp"
#include "Window.hpp"

#include <memory>

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
            Renderer(sdl3::Window &window);

            /// @brief Destroys the renderer.
            ~Renderer();

            /// @brief Creates the render with the window passed.
            /// @param window Window to create renderer with.
            void create(sdl3::Window &window);

            /// @brief Returns the logical width of the renderer.
            int get_width() const noexcept;

            /// @brief Returns the logical height of the renderer.
            int get_height() const noexcept;

            /// @brief Passthrough for SDL_SetRenderDrawColor.
            /// @param drawColor Color to set the renderer to.
            bool set_draw_color(SDL_Color drawColor);

            /// @brief Sets the logical width and height of
            /// @param width Width of the logical presentation.
            /// @param height Height of the logical presentation.
            bool set_logical_width_height(int width, int height, SDL_RendererLogicalPresentation mode);

            /// @brief Sets the render target for the renderer. Passing sdl3::Texture::NullTexture targets the framebuffer.
            bool set_render_target(std::shared_ptr<Texture> &target);

            /// @brief Clears the main render target to the color passed.
            /// @param clearColor Color to clear the target to.
            bool frame_begin(SDL_Color clearColor);

            /// @brief Presents render to screen.
            bool frame_end();

            /// @brief Passthrough for SDL_RenderClear.
            /// @param clearColor Color to clear the renderer to.
            bool clear(SDL_Color clearColor);

            /// @brief Renders a filled rectangle at the coordinates passed with the color passed.
            bool render_fill_rect(int x, int y, int width, int height, SDL_Color color);

            /// @brief This allows the texture renderer to be set.
            friend class Texture;

        private:
            /// @brief Logical width of the renderer.
            int m_width{};

            /// @brief Logical height of the renderer.
            int m_height{};

            /// @brief Underlying SDL3 renderer.
            SDL_Renderer *m_renderer{};
    };
}