#include "WindowTest.hpp"

#include <cstdlib>
#include <format>
#include <fstream>
#include <string>

namespace
{
    constexpr std::string_view WINDOW_A_TITLE = "Window A";
    constexpr std::string_view WINDOW_B_TITLE = "Window B";

    constexpr int WINDOW_A_WIDTH  = 1920;
    constexpr int WINDOW_A_HEIGHT = 1080;

    constexpr int WINDOW_B_WIDTH  = 320;
    constexpr int WINDOW_B_HEIGHT = 720;
}

//                      ---- Construction ----

WindowTest::WindowTest()
    : m_sdl3{}
    , m_input{}
    , m_windowA{WINDOW_A_TITLE, WINDOW_A_WIDTH, WINDOW_A_HEIGHT}
    , m_windowB{WINDOW_B_TITLE, WINDOW_B_WIDTH, WINDOW_B_HEIGHT} {};

//                      ---- Public Functions ----

int WindowTest::run() noexcept
{
    for (;;)
    {
        // Pump.
        m_sdl3.pump_events();

        // Update input.
        m_input.update();

        // Grab escape.
        const sdl3::Input::State escape = m_input.get_key_state(SDL_SCANCODE_ESCAPE);
        if (escape == sdl3::Input::State::Pressed) { return 0; }

        SDL_RenderPresent(m_windowA.get_renderer());
        SDL_RenderPresent(m_windowB.get_renderer());
    }
}