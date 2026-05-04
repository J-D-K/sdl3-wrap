#include "Star.hpp"

#include "SDL3.hpp"

#include <cstdlib>

//                      ---- Construction ----

Star::Star()
    : Object(Object::Type::Star)
{
    // X
    m_x = 960 + (std::rand() % 960);

    // Y
    m_y = std::rand() % 540;

    // Depth.
    m_depth = -3 + (std::rand() % 6);
}

//                      ---- Public Functions ----

void Star::update(Game &game, const sdl3::Input &input) { m_x -= m_depth; }

void Star::render(Game &game, sdl3::Renderer &renderer)
{
    // This is the size to use to render.
    const float renderDimensions = 3 + m_depth;

    // Rect to render with.
    const SDL_FRect renderRect = {.x = static_cast<float>(m_x),
                                  .y = static_cast<float>(m_y),
                                  .w = renderDimensions,
                                  .h = renderDimensions};

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &renderRect);
}