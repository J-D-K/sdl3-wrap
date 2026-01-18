#pragma once

#include "Font.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"

#include <SDL3/SDL.h>
#include <string_view>

namespace sdl3
{
    class SDL3 final
    {
        public:
            /// @brief No copying or moving.
            SDL3(const SDL3 &)            = delete;
            SDL3(SDL3 &&)                 = delete;
            SDL3 &operator=(const SDL3 &) = delete;
            SDL3 &operator=(SDL3 &&)      = delete;

            /// @brief Destructor is public. Cleans up.
            ~SDL3();

            /// @brief Initializes and creates the SDL window.
            /// @param windowTitle Title of the window.
            /// @param windowWidth Width of the window.
            /// @param windowHeight Height of the window.
            /// @return True on success. False on failure.
            static bool initialize(std::string_view windowTitle, int windowWidth, int windowHeight);

            /// @brief Runs the update routine.
            static void update();

            /// @brief Sets the logical presentation of the renderer.
            /// @param width Width of the render area.
            /// @param height Height of the render area.
            /// @return True on success. False on failure.
            static bool set_render_logical_presentation(int width, int height);

            /// @brief Sets the render target to the texture passed. Pass sdl3::Text::NullTexture for the framebuffer.
            /// @param target Render target to render to.
            static bool set_render_target(sdl3::SharedTexture &target);

            /// @brief Starts the frame.
            static void frame_begin();

            /// @brief Ends the frame and presents the renderer to screen.
            static void frame_end();

            /// @brief Returns the internal renderer.
            static SDL_Renderer *get_renderer() noexcept;

            /// @brief Returns a reference to the input instance.
            static sdl3::Input &get_input() noexcept;

            /// @brief Sets the frames per second cap.
            /// @param fps Number of target frames per second.
            static void set_fps_cap(uint64_t fps) noexcept;

        private:
            /// @brief SDL Window.
            SDL_Window *m_window{};

            /// @brief SDL Renderer.
            SDL_Renderer *m_renderer{};

            /// @brief Input instance.
            sdl3::Input m_input{};

            /// @brief The amount of nanoseconds every frame should take.
            uint64_t m_fpsCapTime{};

            /// @brief The time that SDL3::update was called.
            uint64_t m_frameBeginTime{};

            /// @brief Constructor is private.
            SDL3();

            /// @brief Returns the SDL3 instance.
            static SDL3 &get_instance();
    };
}