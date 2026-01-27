#pragma once
#include "CoreComponent.hpp"

#include <SDL3/SDL.h>

namespace sdl3
{
    class SDL3 final : public sdl3::CoreComponent
    {
        public:
            /// @brief Initializes SDL3.
            SDL3()
            {
                // Flags used to init SDL.
                static constexpr SDL_InitFlags SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD;
                m_isInitialized                               = SDL_Init(SDL_INIT_FLAGS);
            }

            /// @brief Quits SDL3.
            ~SDL3() { SDL_Quit(); }

            /// @brief Pump events wrapper.
            inline void pump_events() { SDL_PumpEvents(); }
    };
}