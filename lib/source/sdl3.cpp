#include "sdl3.hpp"

#include "Freetype.hpp"

#include <cmath>

namespace
{
    /// @brief The flags used for initializing SDL.
    constexpr SDL_InitFlags SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD;
}

//                      ---- Construction ----

sdl3::SDL3::SDL3()
    : m_input{} {};

sdl3::SDL3::~SDL3()
{
    // Grab instance.
    SDL3 &instance = SDL3::get_instance();

    // These make things easier to read.
    SDL_Window *window     = instance.m_window;
    SDL_Renderer *renderer = instance.m_renderer;

    // I'm pretty sure this is the order...
    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }

    // Quit SDL altogether now.
    SDL_Quit();
}

//                      ---- Public Functions ----

bool sdl3::SDL3::initialize(std::string_view windowTitle, int windowWidth, int windowHeight)
{
    // Init SDL first.
    const bool sdlInit = SDL_Init(SDL_INIT_FLAGS);
    if (!sdlInit) { return false; }

    // Grab the instance now.
    SDL3 &instance = SDL3::get_instance();

    // Easier to follow and read.
    SDL_Window **window     = &instance.m_window;
    SDL_Renderer **renderer = &instance.m_renderer;

    // Create the window.
    *window = SDL_CreateWindow(windowTitle.data(), windowWidth, windowHeight, 0);
    if (!*window) { return false; }

    // Init renderer.
    *renderer = SDL_CreateRenderer(*window, nullptr);
    if (!*renderer) { return false; }

    // Freetype.
    if (!sdl3::Freetype::initialize()) { return false; }

    return true;
}

void sdl3::SDL3::update()
{
    // Instance.
    SDL3 &instance = SDL3::get_instance();

    // Record the ticks.
    instance.m_beginTicks = static_cast<double>(SDL_GetTicks());

    // Input.
    sdl3::Input &input = instance.m_input;

    // Pump SDL events first.
    SDL_PumpEvents();

    // Update input.
    input.update();
}

bool sdl3::SDL3::set_render_target(sdl3::SharedTexture &target)
{
    // Instance.
    SDL3 &instance = SDL3::get_instance();

    return SDL_SetRenderTarget(instance.m_renderer, target->m_texture);
}

void sdl3::SDL3::frame_begin()
{
    // Instance.
    SDL3 &instance = SDL3::get_instance();

    // Renderer.
    SDL_Renderer *renderer = instance.m_renderer;

    // Set the color and clear the renderer.
    const bool drawColor = SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    const bool cleared   = drawColor && SDL_RenderClear(renderer);
    // To do: Error recording.
    if (!cleared) { return; }
}

void sdl3::SDL3::frame_end()
{
    // Instance
    SDL3 &instance = SDL3::get_instance();

    // Renderer
    SDL_Renderer *renderer = instance.m_renderer;

    // To do: Error logging.
    if (!SDL_RenderPresent(renderer)) { return; }

    // Delay for FPS cap.
    const double fpsCap     = instance.m_fpsCap;
    const double beginTicks = instance.m_beginTicks;
    const double endTicks   = static_cast<double>(SDL_GetTicks());
    const double frameDelta = std::floor(endTicks - beginTicks);
    if (frameDelta >= fpsCap) { return; }

    SDL_Delay(static_cast<uint32_t>(fpsCap - frameDelta));
}

SDL_Renderer *sdl3::SDL3::get_renderer() noexcept
{
    SDL3 &instance = SDL3::get_instance();
    return instance.m_renderer;
}

sdl3::Input &sdl3::SDL3::get_input() noexcept
{
    SDL3 &instance = SDL3::get_instance();
    return instance.m_input;
}

void sdl3::SDL3::set_fps_cap(double fps) noexcept
{
    SDL3 &instance    = SDL3::get_instance();
    instance.m_fpsCap = 1000.0f / fps;
}

//                      ---- Private functions ----

sdl3::SDL3 &sdl3::SDL3::get_instance()
{
    static SDL3 instance{};
    return instance;
}