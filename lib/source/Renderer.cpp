#include "Renderer.hpp"

//                          ---- Construction ----

sdl3::Renderer::Renderer(sdl3::Window &window)
    : m_width{window.get_width()}
    , m_height{window.get_height()}
{
    m_renderer = SDL_CreateRenderer(static_cast<SDL_Window *>(window), nullptr);
    if (!m_renderer) { return; }

    m_initialized = true;
}

sdl3::Renderer::~Renderer()
{
    if (!m_initialized) { return; }
    SDL_DestroyRenderer(m_renderer);
}

//                      ---- Public Functions ----

int sdl3::Renderer::get_logical_width() const noexcept { return m_width; }

int sdl3::Renderer::get_logical_height() const noexcept { return m_height; }

bool sdl3::Renderer::set_logical_presentation(int width, int height)
{
    // Store.
    m_width  = width;
    m_height = height;

    return SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
}

bool sdl3::Renderer::set_render_target(sdl3::SharedTexture &target) { return SDL_SetRenderTarget(m_renderer, *target); }

bool sdl3::Renderer::set_render_clip(int x, int y, int width, int height)
{
    const SDL_Rect renderClip = {.x = x, .y = y, .w = width, .h = height};
    return SDL_SetRenderClipRect(m_renderer, &renderClip);
}

bool sdl3::Renderer::frame_begin(SDL_Color clear)
{
    const bool target = SDL_SetRenderTarget(m_renderer, nullptr);
    const bool color  = target && SDL_SetRenderDrawColor(m_renderer, clear.r, clear.g, clear.b, clear.a);

    return color && SDL_RenderClear(m_renderer);
}

bool sdl3::Renderer::frame_end() { return SDL_RenderPresent(m_renderer); }

sdl3::Renderer::operator SDL_Renderer *() const noexcept { return m_renderer; }

//                      ---- Private Functions ----