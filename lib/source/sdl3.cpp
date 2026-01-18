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

    // Frame time.
    SDL3::set_fps_cap(60);

    return true;
}

void sdl3::SDL3::update()
{
    // Instance.
    SDL3 &instance = SDL3::get_instance();

    // Record the ticks.
    instance.m_frameBeginTime = SDL_GetTicksNS();

    // Input.
    sdl3::Input &input = instance.m_input;

    // Pump SDL events first.
    SDL_PumpEvents();

    // Update input.
    input.update();
}

bool sdl3::SDL3::set_render_logical_presentation(int width, int height)
{
    // Instance.
    SDL3 &instance = SDL3::get_instance();

    return SDL_SetRenderLogicalPresentation(instance.m_renderer, width, height, SDL_LOGICAL_PRESENTATION_STRETCH);
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
    const uint64_t fpsCap     = instance.m_fpsCapTime;
    const uint64_t beginTicks = instance.m_frameBeginTime;
    const uint64_t endTicks   = SDL_GetTicksNS();
    const uint64_t frameDelta = endTicks - beginTicks;
    if (frameDelta >= fpsCap) { return; }

    const uint32_t sdlDelayTime = fpsCap - frameDelta;
    SDL_DelayPrecise(sdlDelayTime);
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

void sdl3::SDL3::set_fps_cap(uint64_t fps) noexcept
{
    constexpr uint64_t NANOSECONDS_IN_SECOND = 1e+9;

    SDL3 &instance        = SDL3::get_instance();
    instance.m_fpsCapTime = NANOSECONDS_IN_SECOND / fps;
}

//                      ---- Private functions ----

sdl3::SDL3 &sdl3::SDL3::get_instance()
{
    static SDL3 instance{};
    return instance;
}