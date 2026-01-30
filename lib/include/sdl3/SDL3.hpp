#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>
#include <vector>

namespace sdl3
{
    class SDL3 final : public sdl3::CoreComponent
    {
        public:
            /// @brief Initializes SDL3.
            SDL3()
            {
                // Flags used to init SDL.
                static constexpr SDL_InitFlags SDL_INIT_FLAGS =
                    SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD | SDL_INIT_VIDEO;

                // Init SDL.
                m_isInitialized = SDL_Init(SDL_INIT_FLAGS);

                // Load the display info.
                SDL3::load_display_dimensions();
            }

            /// @brief Quits SDL3.
            ~SDL3() { SDL_Quit(); }

            /// @brief Returns the width of the primary display.
            int get_display_width() const noexcept { return m_display.w; }

            /// @brief Returns the height of the primary display.
            int get_display_height() const noexcept { return m_display.h; }

            /// @brief Pump events wrapper.
            inline void pump_events() { SDL_PumpEvents(); }

        private:
            /// @brief Primary display dimensions.
            SDL_Rect m_display{};

            /// @brief Attempts to load the primary display dimensions.
            void load_display_dimensions()
            {
                // Grab the primary display.
                const SDL_DisplayID primaryDisplay = SDL_GetPrimaryDisplay();

                // Get the bounds/dimensions.
                SDL_GetDisplayBounds(primaryDisplay, &m_display);
            }
    };
}