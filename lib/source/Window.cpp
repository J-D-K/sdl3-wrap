#include "Window.hpp"

//                      ---- Construction ----

sdl3::Window::Window(std::string_view windowTitle, int windowWidth, int windowHeight)
    : m_width{windowWidth}
    , m_height{windowHeight}
{
    m_window = SDL_CreateWindow(windowTitle.data(), windowWidth, windowHeight, 0);
    if (!m_window) { return; }

    m_initialized = true;
}

sdl3::Window::~Window()
{
    if (m_window) { SDL_DestroyWindow(m_window); }
}

//                      ---- Public Functions ----

int sdl3::Window::get_width() const noexcept { return m_width; }

int sdl3::Window::get_height() const noexcept { return m_height; }

sdl3::Window::operator SDL_Window *() const noexcept { return m_window; }

//                      ---- Private Functions ----