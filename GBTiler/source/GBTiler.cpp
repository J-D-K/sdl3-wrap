#include "GBTiler.hpp"

#include "ui/Menu.hpp"
#include "ui/Text.hpp"
#include "ui/colors.hpp"
#include "window.hpp"

//                      ---- Construction ----

GBTiler::GBTiler(std::span<const char *> argv)
    : m_sdl3{}
    , m_window{window::TITLE, window::WIDTH, window::HEIGHT}
    , m_renderer{m_window}
    , m_input{}
    , m_frameLimiter{}
{
    // Init texture.
    sdl3::Texture::set_renderer(m_renderer);

    // Setup menus.
    GBTiler::initialize_menu_bar();
    GBTiler::initialize_file_menu();
    GBTiler::initialize_edit_menu();

    // These are for printing debug info.
    m_mouseX = GBTiler::new_ui_element<ui::Text>(0, 32, ui::colors::WHITE, "");
    m_mouseY = GBTiler::new_ui_element<ui::Text>(0, 50, ui::colors::WHITE, "");
}

//                      ---- Public Functions ----

int GBTiler::run()
{
    for (;;)
    {
        // Pump.
        m_sdl3.pump_events();

        // Update input instance.
        m_input.update();

        // Handle escape.
        const sdl3::Input::State escape = m_input.get_key_state(SDL_SCANCODE_ESCAPE);
        if (escape == sdl3::Input::State::Pressed) { return 0; }

        // Begin frame limiter.
        m_frameLimiter.begin_cap();

        // Update the strings for these.
        const std::string mouseX = std::format("Mouse X: {}", m_input.get_mouse_x());
        const std::string mouseY = std::format("Mouse Y: {}", m_input.get_mouse_y());
        m_mouseX->set_text(mouseX);
        m_mouseY->set_text(mouseY);

        // Update and render.
        GBTiler::update();
        GBTiler::render();

        // Engage frame limiter.
        m_frameLimiter.end_cap();
    }
}

//                      ---- Private Functions ----

void GBTiler::update()
{
    for (auto &element : m_elements) { element->update(m_input); }
}

void GBTiler::render()
{
    m_renderer.frame_begin(ui::colors::CLEAR);
    for (auto &element : m_elements) { element->render(m_renderer); }
    m_renderer.frame_end();
}

void GBTiler::initialize_menu_bar()
{
    // Create the menu bar.
    m_menuBar = GBTiler::new_ui_element<ui::MenuBar>();
}

void GBTiler::initialize_file_menu()
{
    // Create the menu.
    auto fileMenu = ui::Menu::create("File");

    // Push to menu bar.
    m_menuBar->add_menu(fileMenu);
}

void GBTiler::initialize_edit_menu()
{
    auto editMenu = ui::Menu::create("Edit");
    m_menuBar->add_menu(editMenu);
}