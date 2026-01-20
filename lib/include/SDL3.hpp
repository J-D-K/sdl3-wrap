#pragma once

#include "Font.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "Window.hpp"

#include <SDL3/SDL.h>
#include <string_view>

namespace sdl3
{
    class SDL3 final
    {
        public:
            // No copying or moving.
            SDL3(const SDL3 &)            = delete;
            SDL3(SDL3 &&)                 = delete;
            SDL3 &operator=(const SDL3 &) = delete;
            SDL3 &operator=(SDL3 &&)      = delete;

            /// @brief Constructor. Initializes SDL3 and freetype.
            SDL3();

            /// @brief Destructor. Quits SDL.
            ~SDL3();

            /// @brief Returns whether or not initializing SDL3 was successful.
            bool is_initialized() const noexcept;

            /// @brief Wrapper around SDL_PumpEvents.
            void pump_events();

        private:
            /// @brief Stores whether or not initialization was successful.
            bool m_isInitialized{};
    };
}