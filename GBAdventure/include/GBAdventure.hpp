#pragma once
#include "objects/Object.hpp"
#include "sdl3.hpp"

class GBAdventure final
{
    public:
        /// @brief Constructor. Initializes the game.
        GBAdventure();

        /// @brief Runs the game.
        int run();

    private:
        /// @brief SDL3 instance. Inits SDL3.
        sdl3::SDL3 m_sdl{};

        /// @brief SDL3 window.
        sdl3::Window m_window{};

        /// @brief SDL3 renderer.
        sdl3::Renderer m_renderer{};

        /// @brief SDL3 input wrapper.
        sdl3::Input m_input{};

        /// @brief Runs the update routine.
        void update();

        /// @brief Runs the render routine.
        void render();
};