#pragma once
#include "CoreComponent.hpp"
#include "Window.hpp"

#include <SDL3/SDL.h>

namespace sdl3
{
    /// @brief SDL3 renderer wrapper class.
    class Renderer final : public sdl3::CoreComponent
    {
        public:
            // No copies or moving.
            Renderer(const Renderer &)            = delete;
            Renderer(Renderer &&)                 = delete;
            Renderer &operator=(const Renderer &) = delete;
            Renderer &operator=(Renderer &&)      = delete;

            /// @brief Default.
            Renderer() = default;

            /// @brief Constructor.
            /// @param window Window to create the renderer with.
            Renderer(sdl3::Window &window);

            /// @brief Destroys the renderer.
            ~Renderer();

            /// @brief Returns the logical width.
            int get_logical_width() const noexcept;

            /// @brief Returns the logical height.
            int get_logical_height() const noexcept;

            /// @brief Sets the logical width and height of the renderer.
            bool set_logical_presentation(int width, int height);

            /// @brief Sets the target to the default framebuffer and clears it to the color passed.
            /// @param clear Color to clear the framebuffer to.
            bool frame_begin(SDL_Color clear);

            /// @brief Ends the frame and presents it to screen.
            bool frame_end();

            /// @brief Returns the underlying SDL_Renderer.
            operator SDL_Renderer *() const noexcept;

        private:
            /// @brief Underlying SDL_Renderer.
            SDL_Renderer *m_renderer{};

            /// @brief Logical width.
            int m_width{};

            /// @brief Logical height.
            int m_height{};
    };
}