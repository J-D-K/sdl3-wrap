#pragma once
#include "SDL3.hpp"

#include <vector>

class WindowTest final
{
    public:
        /// @brief This is to test multiple windows.
        WindowTest();

        /// @brief Runs the window test.
        int run() noexcept;

    private:
        // SDL Instance.
        sdl3::SDL3 m_sdl3{};

        // Input instance.
        sdl3::Input m_input{};

        /// @brief Window A.
        sdl3::Window m_windowA{};

        /// @brief Window B
        sdl3::Window m_windowB{};
};