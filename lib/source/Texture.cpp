#include "Texture.hpp"

#include "sdl3.hpp"

#include <SDL3_image/SDL_image.h>

//                      ---- Construction ----

sdl3::Texture::Texture(std::string_view texturePath)
{
    Texture::initialize_static_members();

    // Load the texture with SDL_image.
    m_texture = IMG_LoadTexture(sdl3::SDL3::get_renderer(), texturePath.data());
    if (!m_texture) { return; }

    // Get the width and height.
    const bool dimensions = SDL_GetTextureSize(m_texture, &m_width, &m_height);
    if (!dimensions) { return; }

    // Good to go?
    m_isValid = true;
}

sdl3::Texture::Texture(sdl3::Surface &surface)
    : m_width{static_cast<float>(surface->w)}
    , m_height{static_cast<float>(surface->h)}
{
    Texture::initialize_static_members();

    m_texture = SDL_CreateTextureFromSurface(sm_renderer, surface.get());
    if (!m_texture) { return; }

    m_isValid = true;
}

sdl3::Texture::Texture(int width, int height, SDL_TextureAccess accessFlags)
    : m_width{static_cast<float>(width)}
    , m_height{static_cast<float>(height)}
{
    Texture::initialize_static_members();

    m_texture = SDL_CreateTexture(sm_renderer, SDL_PIXELFORMAT_RGBA8888, accessFlags, width, height);
    if (!m_texture) { return; }

    m_isValid = true;
}

sdl3::Texture::~Texture()
{
    if (m_texture) { SDL_DestroyTexture(m_texture); }
}

//                      ---- Public Functions ----

bool sdl3::Texture::render_to(sdl3::SharedTexture &target, int x, int y)
{
    // Rendering rects.
    const SDL_FRect sourceRect = {.x = 0.0f, .y = 0.0f, .w = m_width, .h = m_height};
    const SDL_FRect destRect   = {.x = static_cast<float>(x), .y = static_cast<float>(y), .w = m_width, .h = m_height};

    // Set the render target. Bail on failure.
    const bool targetSet = SDL_SetRenderTarget(sm_renderer, target->m_texture);
    if (!targetSet) { return false; }

    // Just return this. It's easier.
    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_to_stretched(sdl3::SharedTexture &target, int x, int y, int width, int height)
{
    // Rects.
    const SDL_FRect sourceRect = {.x = 0.0f, .y = 0.0f, .w = m_width, .h = m_height};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(width),
                                  .h = static_cast<float>(height)};

    const bool targetSet = SDL_SetRenderTarget(sm_renderer, target->m_texture);
    if (!targetSet) { return false; }

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_part_to(sdl3::SharedTexture &target,
                                   int x,
                                   int y,
                                   int sourceX,
                                   int sourceY,
                                   int sourceWidth,
                                   int sourceHeight)
{
    // Rects.
    const SDL_FRect sourceRect = {.x = static_cast<float>(sourceX),
                                  .y = static_cast<float>(sourceY),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};

    const bool setTarget = SDL_SetRenderTarget(sm_renderer, target->m_texture);
    if (!setTarget) { return false; }

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

bool sdl3::Texture::render_part_to_stretched(sdl3::SharedTexture &target,
                                             int x,
                                             int y,
                                             int width,
                                             int height,
                                             int sourceX,
                                             int sourceY,
                                             int sourceWidth,
                                             int sourceHeight)
{
    const SDL_FRect sourceRect = {.x = static_cast<float>(sourceX),
                                  .y = static_cast<float>(sourceY),
                                  .w = static_cast<float>(sourceWidth),
                                  .h = static_cast<float>(sourceHeight)};
    const SDL_FRect destRect   = {.x = static_cast<float>(x),
                                  .y = static_cast<float>(y),
                                  .w = static_cast<float>(width),
                                  .h = static_cast<float>(height)};

    const bool setTarget = SDL_SetRenderTarget(sm_renderer, target->m_texture);
    if (!setTarget) { return false; }

    return SDL_RenderTexture(sm_renderer, m_texture, &sourceRect, &destRect);
}

//                      ---- Private Functions ----

void sdl3::Texture::initialize_static_members()
{
    if (sm_renderer) { return; }

    sm_renderer = sdl3::SDL3::get_renderer();
}