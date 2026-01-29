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
    const bool initFailed = !m_sdl3.is_initialized() || !m_window.is_initialized() || !m_renderer.is_initialized();
    if (initFailed) { return; }

    // Should be running.
    m_running = true;

    // Init texture.
    sdl3::Texture::set_renderer(m_renderer);

    // Setup menus.
    GBTiler::initialize_menu_bar();

    // These are for printing debug info.
    const int mouseCoordsX = window::HEIGHT - ui::font::SIZE * 2.5;
    m_mouseCoords          = GBTiler::new_ui_element<ui::Text>(0, mouseCoordsX, ui::colors::WHITE, "");
}

//                      ---- Public Functions ----

int GBTiler::run()
{
    while (m_running)
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
        const uint8_t mouseLeft   = static_cast<uint8_t>(m_input.get_mouse_button_state(sdl3::Input::MouseButton::Left));
        const uint8_t mouseMiddle = static_cast<uint8_t>(m_input.get_mouse_button_state(sdl3::Input::MouseButton::Middle));
        const uint8_t mouseRight  = static_cast<uint8_t>(m_input.get_mouse_button_state(sdl3::Input::MouseButton::Right));

        const std::string mouseCoords = std::format("Mouse X: {}\nMouse Y: {}", m_input.get_mouse_x(), m_input.get_mouse_y());
        m_mouseCoords->set_text(mouseCoords);

        // Update and render.
        GBTiler::update();
        GBTiler::render();

        // Engage frame limiter.
        m_frameLimiter.end_cap();
    }
    return -1;
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

    // Create all of the main menu labels.
    GBTiler::initialize_file_menu();
    GBTiler::initialize_layer_menu();
}

void GBTiler::initialize_file_menu()
{
    // Create the menu.
    auto fileMenu = ui::Menu::create("File");

    // Option lambdas.
    auto exitLambda = [this]() { this->m_running = false; };

    // Add the options.
    fileMenu->add_sub_option("Open", nullptr);
    fileMenu->add_sub_option("Save", nullptr);
    fileMenu->add_sub_option("Save As", nullptr);
    fileMenu->add_sub_option("Exit", exitLambda);

    // Push to menu bar.
    m_menuBar->add_menu(fileMenu);
}

void GBTiler::initialize_layer_menu()
{
    auto layerMenu = ui::Menu::create("Layer");
    m_menuBar->add_menu(layerMenu);
}