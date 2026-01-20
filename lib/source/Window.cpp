#include "Window.hpp"

//                      ---- Construction ----

sdl3::Window::Window(std::string_view windowTitle, int windowWidth, int windowHeight)
    : m_width{windowWidth}
    , m_height{windowHeight}
    , m_logicalWidth{windowWidth}
    , m_logicalHeight{windowHeight}
{
    m_window = SDL_CreateWindow(windowTitle.data(), windowWidth, windowHeight, 0);
    if (!m_window) { return; }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) { return; }

    m_isInitialized = true;
}

sdl3::Window::~Window()
{
    if (m_renderer) { SDL_DestroyRenderer(m_renderer); }
    if (m_window) { SDL_DestroyWindow(m_window); }
}

//                      ---- Public Functions ----

bool sdl3::Window::is_initialized() const noexcept { return m_isInitialized; }

int sdl3::Window::get_width() const noexcept { return m_width; }

int sdl3::Window::get_height() const noexcept { return m_height; }

SDL_Renderer *sdl3::Window::get_renderer() const noexcept { return m_renderer; }

bool sdl3::Window::set_logical_render_dimensions(int width, int height)
{
    // Store.
    m_logicalWidth  = width;
    m_logicalHeight = height;

    return SDL_SetRenderLogicalPresentation(m_renderer, m_logicalWidth, m_logicalHeight, SDL_LOGICAL_PRESENTATION_STRETCH);
}