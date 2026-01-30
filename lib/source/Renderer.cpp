#include "sdl3/Renderer.hpp"

#include "sdl3/ResourceManager.hpp"
#include "sdl3/Texture.hpp"

//                      ---- Construction ----

sdl3::Renderer::Renderer(sdl3::Window &window) { Renderer::create(window); }

sdl3::Renderer::~Renderer()
{
    if (!m_renderer) { return; }
    SDL_DestroyRenderer(m_renderer);
}

//                      ---- Public Functions ----

void sdl3::Renderer::create(sdl3::Window &window)
{
    m_renderer = SDL_CreateRenderer(window.m_window, nullptr);
    if (!m_renderer) { return; }

    // Record these.
    m_width  = window.m_width;
    m_height = window.m_height;

    m_isInitialized = true;
}

int sdl3::Renderer::get_width() const noexcept { return m_width; }

int sdl3::Renderer::get_height() const noexcept { return m_height; }

bool sdl3::Renderer::set_draw_color(SDL_Color drawColor)
{
    return SDL_SetRenderDrawColor(m_renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

bool sdl3::Renderer::set_logical_width_height(int width, int height, SDL_RendererLogicalPresentation mode)
{
    const bool setLogical = SDL_SetRenderLogicalPresentation(m_renderer, width, height, mode);
    if (!setLogical) { return false; }

    m_width  = width;
    m_height = height;

    return true;
}

bool sdl3::Renderer::set_render_target(std::shared_ptr<Texture> &target)
{
    return SDL_SetRenderTarget(m_renderer, target->m_texture);
}

bool sdl3::Renderer::frame_begin(SDL_Color clearColor)
{
    // Set back to the original target just in case.
    if (!Renderer::set_render_target(sdl3::Texture::NullTexture)) { return false; }

    // Clear.
    return Renderer::clear(clearColor);
}

bool sdl3::Renderer::frame_end() { return SDL_RenderPresent(m_renderer); }

bool sdl3::Renderer::clear(SDL_Color clearColor)
{
    if (!Renderer::set_draw_color(clearColor)) { return false; }

    return SDL_RenderClear(m_renderer);
}

bool sdl3::Renderer::render_fill_rect(int x, int y, int width, int height, SDL_Color color)
{
    if (!Renderer::set_draw_color(color)) { return false; }

    const SDL_FRect rect = {.x = static_cast<float>(x),
                            .y = static_cast<float>(y),
                            .w = static_cast<float>(width),
                            .h = static_cast<float>(height)};

    return SDL_RenderFillRect(m_renderer, &rect);
}