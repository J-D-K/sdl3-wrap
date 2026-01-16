#include "TestGame.hpp"

#include "sdl3.hpp"

#include <string_view>

namespace
{
    constexpr std::string_view WINDOW_TITLE = "SDL3 Wrapper Test";
    constexpr int WINDOW_WIDTH              = 1920;
    constexpr int WINDOW_HEIGHT             = 1080;
}

//                      ---- Construction ----

TestGame::TestGame()
{
    // Init SDL.
    if (!sdl3::SDL3::initialize(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) { return; }

    m_testTexture = sdl3::TextureManager::load_resource("./test_texture.png");

    m_isRunning = true;
}

//                      ---- Public Functions ----

bool TestGame::is_running() const noexcept { return m_isRunning; }

void TestGame::update() noexcept
{
    // Run the SDL3 update routine.
    sdl3::SDL3::update();

    // Grab input.
    sdl3::Input &input = sdl3::SDL3::get_input();

    // Grab escape.
    const sdl3::Input::KeyStates escapeState = input.get_key_state(SDL_SCANCODE_ESCAPE);

    // If Escape is pressed or held, stop running.
    if (escapeState == sdl3::Input::KeyStates::Pressed) { m_isRunning = false; }
}

void TestGame::render() noexcept
{
    sdl3::SDL3::frame_begin();
    m_testTexture->render_to(sdl3::Texture::NullTexture, 0, 0);

    sdl3::SDL3::frame_end();
}