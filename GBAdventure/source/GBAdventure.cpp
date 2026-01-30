#include "GBAdventure.hpp"

#include "StateManager.hpp"
#include "graphics/colors.hpp"
#include "states/Titlescreen.hpp"
#include "window.hpp"

#include <string_view>

//                      ---- Construction ----

GBAdventure::GBAdventure()
    : m_sdl{}
    , m_window{window::TITLE, window::WIDTH, window::HEIGHT}
    , m_renderer{m_window}
    , m_input{}
{
    // Init texture.
    sdl3::Texture::set_renderer(m_renderer);

    // Set renderer logical.
    m_renderer.set_logical_width_height(window::LOGICAL_WIDTH, window::LOGICAL_HEIGHT, SDL_LOGICAL_PRESENTATION_STRETCH);

    // Push the title screen.
    StateManager::create_push_state<states::Titlescreen>();
}

//                      ---- Public Functions ----

int GBAdventure::run()
{
    for (;;)
    {
        // Pump SDL Events.
        m_sdl.pump_events();

        // Update input instance.
        m_input.update();

        // Handle escape.
        const sdl3::Input::State escape = m_input.get_key_state(SDL_SCANCODE_ESCAPE);
        if (escape == sdl3::Input::State::Pressed) { return 0; }

        GBAdventure::update();
        GBAdventure::render();
    }
}

//                      ---- Private Functions ----

void GBAdventure::update() { StateManager::update(m_input); }

void GBAdventure::render()
{
    // Clear the renderer
    m_renderer.frame_begin(graphics::palette::LIGHT);
    StateManager::render(m_renderer);
    m_renderer.frame_end();
}