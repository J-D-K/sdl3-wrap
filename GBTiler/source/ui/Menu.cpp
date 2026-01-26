#include "ui/Menu.hpp"

#include "ui/colors.hpp"
#include "ui/font.hpp"

namespace
{
    constexpr int MENU_PADDING = 24;
    constexpr int MENU_HEIGHT  = 18;
}

//                      ---- Construction ----

ui::Menu::Menu(std::string_view menuName)
    : m_label{menuName}
{
    // Ensure font is loaded.
    Menu::initialize_static_members();

    // Get the width of the label. The final width is the width of the label plus the padding from above.
    m_labelWidth = sm_uiFont->get_text_width(m_label);
    m_width      = m_labelWidth + MENU_PADDING;

    // Set the height and label position.
    m_height = MENU_HEIGHT;
    m_labelY = m_y + ((m_height / 2) - (ui::font::SIZE / 2));
}

//                      ---- Public Functions ----

void ui::Menu::add_sub_option(std::string_view option, std::function<void()> onClick)
{
    m_subOptions.push_back(std::make_pair(std::string{option}, onClick));
}

void ui::Menu::update(const sdl3::Input &input)
{
    // Conditions for updating the state of the menu.
    const bool mouseWithin = Element::mouse_is_within(input);
    const bool isIdle      = (m_state == State::Hovered || m_state == State::Clicked) && !mouseWithin;
    const bool isHovered   = m_state == State::Idle && mouseWithin;

    if (isIdle) { m_state = State::Idle; }
    else if (isHovered) { m_state = State::Hovered; }
}

void ui::Menu::render(sdl3::Renderer &renderer)
{
    // Render the back.
    switch (m_state)
    {
        case State::Idle:    Menu::render_idle(renderer); break;
        case State::Hovered:
        case State::Clicked: Menu::render_hover(renderer); break;
        default:             return;
    }
}

//                      ---- Private Functions ----

void ui::Menu::initialize_static_members()
{
    if (sm_uiFont) { return; }

    sm_uiFont = sdl3::FontManager::load_resource(ui::font::PATH, ui::font::PATH, ui::font::SIZE);
}

void ui::Menu::render_idle(sdl3::Renderer &renderer)
{
    // Back.
    renderer.render_fill_rect(m_x, m_y, m_width, m_height, ui::colors::MENU);

    // Label.
    sm_uiFont->render_text(m_labelX, m_labelY, ui::colors::BLACK, m_label);
}

void ui::Menu::render_hover(sdl3::Renderer &renderer)
{
    renderer.render_fill_rect(m_x, m_y, m_width, m_height, ui::colors::MENU_HOVER);
    sm_uiFont->render_text(m_labelX, m_labelY, ui::colors::WHITE, m_label);
}