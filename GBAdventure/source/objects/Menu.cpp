#include "objects/Menu.hpp"

#include "graphics/colors.hpp"
#include "graphics/font.hpp"

//                      ---- Construction ----

objects::Menu::Menu() { Menu::initialize_static_members(); }

objects::Menu::Menu(int x, int y, std::span<const std::string_view> optionsList)
    : Menu()
{
    // Set the X and Y.
    Menu::set_x_y(x, y);

    // Loop and add options passed.
    for (std::string_view option : optionsList) { m_options.push_back(std::move(std::string{option})); }
}

//                      ---- Public Functions ----

int objects::Menu::get_selected() const noexcept { return m_selected; }

void objects::Menu::set_selected(int selected) noexcept { m_selected = selected; }

void objects::Menu::set_x_y(int x, int y) noexcept
{
    m_x = x;
    m_y = y;
}

void objects::Menu::update(const sdl3::Input &input)
{
    // Grab the update and down keys.
    const bool moveUp   = input.get_key_state(SDL_SCANCODE_UP) == sdl3::Input::State::Pressed;
    const bool moveDown = input.get_key_state(SDL_SCANCODE_DOWN) == sdl3::Input::State::Pressed;

    if (moveUp) { m_selected--; }
    else if (moveDown) { m_selected++; }

    if (m_selected < 0) { m_selected = m_options.size() - 1; }
    else if (m_selected >= m_options.size()) { m_selected = 0; }
}

void objects::Menu::render(sdl3::Renderer &renderer)
{
    const size_t optionCount = m_options.size();

    // All of the pixel fonts I've found are weird and need to be offset to be rendered?
    for (size_t i = 0, currentY = m_y - 6; i < optionCount; i++, currentY += 12)
    {
        if (m_selected == i) { sm_pointer->render(m_x - 20, currentY + 8); }

        sm_font->render_text(m_x, currentY, graphics::palette::DARK, m_options.at(i));
    }
}

//                      ---- Private Members ----

void objects::Menu::initialize_static_members()
{
    static constexpr std::string_view POINTER_PATH = "./assets/PointerA.png";

    if (sm_pointer) { return; }

    // Load the pointer.
    sm_pointer = sdl3::TextureManager::load_resource(POINTER_PATH, POINTER_PATH);
    sm_pointer->set_scale_mode(SDL_SCALEMODE_NEAREST);

    // Load the font.
    sm_font = sdl3::FontManager::load_resource(graphics::font::FONT_PATH, graphics::font::FONT_PATH, graphics::font::FONT_SIZE);
}