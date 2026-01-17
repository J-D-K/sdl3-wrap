#pragma once

#include "sdl3.hpp"

#include <vector>

class TestGame final
{
    public:
        /// @brief Constructor. Inits SDL and creates window.
        TestGame();

        /// @brief Returns whether or not initialization was successful and the game is still running.
        bool is_running() const noexcept;

        /// @brief Runs the update routine.
        void update() noexcept;

        /// @brief Runs the render routine.
        void render() noexcept;

    private:
        /// @brief Whether or not the game is running.
        bool m_isRunning{};

        /// @brief Test texture for rendering.
        sdl3::SharedTexture m_testTexture{};

        /// @brief Test font.
        sdl3::SharedFont m_testFont{};
};