#include "Texture.hpp"

#include "Renderer.hpp"

#include <SDL3_image/SDL_image.h>

//                      ---- Construction ----

sdl3::Texture::Texture(std::string_view texturePath)
{
    if (!sm_renderer) { return; }

    // Load the texture with SDL_image.
    m_texture = IMG_LoadTexture(sm_renderer, texturePath.data());
    if (!m_texture) { return; }

    // Get the width and height.
    const bool dimensions = SDL_GetTextureSize(m_texture, &m_width, &m_height);
    if (!dimensions) { return; }

    // Good to go?
    m_initialized = true;
}

sdl3::Texture::Texture(sdl3::Surface &surface)
    : m_width{static_cast<float>(surface->w)}
    , m_height{static_cast<float>(surface->h)}
{
    if (!sm_renderer) { return; }

    m_texture = SDL_CreateTextureFromSurface(sm_renderer, surface.get());
    if (!m_texture) { return; }

    m_initialized = true;
}

sdl3::Texture::Texture(std::span<const uint8_t> data)
{
    if (!sm_renderer) { return; }

    // SDL IO.
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), data.size());
    m_texture        = IMG_LoadTexture_IO(sm_renderer, io, true);
    if (!m_texture) { return; }

    m_initialized = true;
}

sdl3::Texture::Texture(int width, int height, SDL_TextureAccess accessFlags)
    : m_width{static_cast<float>(width)}
    , m_height{static_cast<float>(height)}
{
    if (!sm_renderer) { return; }

    m_texture = SDL_CreateTexture(sm_renderer, SDL_PIXELFORMAT_ABGR8888, accessFlags, width, height);
    if (!m_texture) { return; }

    m_initialized = true;
}

sdl3::Texture::~Texture()
{
    if (m_texture) { SDL_DestroyTexture(m_texture); }
}

//                      ---- Public Functions ----

void sdl3::Texture::initialize(sdl3::Renderer &renderer) { sm_renderer = static_cast<SDL_Renderer *>(renderer); }

int sdl3::Texture::get_width() const noexcept { return m_width; }

int sdl3::Texture::get_height() const noexcept { return m_height; }

bool sdl3::Texture::set_alpha_mod(uint8_t alpha) { return SDL_SetTextureAlphaMod(m_texture, alpha); }

bool sdl3::Texture::set_color_mod(SDL_Color colorMod)
{ return SDL_SetTextureColorMod(m_texture, colorMod.r, colorMod.g, colorMod.b); }

bool sdl3::Texture::set_scale_mode(SDL_ScaleMode scaleMode) { return SDL_SetTextureScaleMode(m_texture, scaleMode); }

bool sdl3::Texture::render(int x, int y)
{
    if (!m_initialized) { return false; }

    // Rendering rects.
    const SDL_FRect sourceRect = {.x = 0.0f, .y = 0.0f, .w = m_width, .h = m_height};
    const SDL_FRect destRect   = {.x = static_cast<float>(x), .y = static_cast<float>(y), .w = m_width, .h = m_height};

    // Just return this. It's easier.
    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_stretched(int x, int y, int width, int height)
{
    if (!m_initialized) { return false; }

    // Rects.
    const SDL_FRect sourceRect = {.x = 0.0f, .y = 0.0f, .w = m_width, .h = m_height};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(width),
                                  .h = static_cast<float>(height)};

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_part(int x, int y, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
    if (!m_initialized) { return false; }

    // Rects.
    const SDL_FRect sourceRect = {.x = static_cast<float>(sourceX),
                                  .y = static_cast<float>(sourceY),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_part_stretched(int x,
                                          int y,
                                          int width,
                                          int height,
                                          int sourceX,
                                          int sourceY,
                                          int sourceWidth,
                                          int sourceHeight)
{
    if (!m_initialized) { return false; }

    const SDL_FRect sourceRect = {.x = static_cast<float>(sourceX),
                                  .y = static_cast<float>(sourceY),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(width),
                                  .h = static_cast<float>(height)};

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

sdl3::Texture::operator SDL_Texture *() const noexcept { return m_texture; }

//                      ---- Private Functions ----