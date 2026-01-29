#include "ui/MenuOption.hpp"

#include "ui/colors.hpp"
#include "ui/menudims.hpp"

//                      ---- Construction ----

ui::MenuOption::MenuOption(int x, int y, std::string_view label, std::function<void()> onClick)
    : Element(x, y)
    , m_label{label}
    , m_onClick{onClick}
{
    // Get the width of the label.
    m_labelWidth = sm_uiFont->get_text_width(m_label);

    // Set the width of the entire option.
    m_width  = m_labelWidth + ui::menudims::PADDING;
    m_height = ui::menudims::HEIGHT;

    // Calc label position.
    m_labelY = m_y + ((m_height / 2) - (ui::font::SIZE / 2));
}

//                      ---- Public Functions ----

void ui::MenuOption::update(const sdl3::Input &input)
{
    switch (m_state)
    {
        case State::Idle:  MenuOption::update_idle(input); break;
        case State::Hover: MenuOption::update_hover(input); break;
        default:           return;
    }
}

void ui::MenuOption::render(sdl3::Renderer &renderer)
{
    switch (m_state)
    {
        case State::Idle:  MenuOption::render_idle(renderer); break;
        case State::Hover: MenuOption::render_hover(renderer); break;
        default:           return;
    }
}

//                      ---- Private Functions ----

void ui::MenuOption::update_idle(const sdl3::Input &input) noexcept
{
    // State switching conditions.
    const bool isHovered = Element::mouse_is_within(input);

    if (isHovered) { m_state = State::Hover; }
    else
    {
        m_state = State::Idle;
    }
}

void ui::MenuOption::update_hover(const sdl3::Input &input) noexcept
{
    // Whether or not the left button was clicked.
    const bool leftClick = input.get_mouse_button_state(sdl3::Input::MouseButton::Left) == sdl3::Input::State::Pressed;

    // Whether or not the the mouse is still within.
    const bool isWithin = Element::mouse_is_within(input);

    // Conditions.
    const bool toIdle        = !isWithin;
    const bool performAction = leftClick && isWithin;

    if (toIdle) { m_state = State::Idle; }
    else if (performAction && m_onClick) { m_onClick(); }
}

void ui::MenuOption::render_idle(sdl3::Renderer &renderer)
{
    // Render the back rect.
    renderer.render_fill_rect(m_x, m_y, m_width, m_height, ui::colors::MENU);
    // Render the label.
    sm_uiFont->render_text(m_x + ui::menudims::SUB_OFFSET_X, m_labelY, ui::colors::BLACK, m_label);
}

void ui::MenuOption::render_hover(sdl3::Renderer &renderer)
{
    renderer.render_fill_rect(m_x, m_y, m_width, m_height, ui::colors::MENU_HOVER);
    sm_uiFont->render_text(m_x + ui::menudims::SUB_OFFSET_X, m_labelY, ui::colors::WHITE, m_label);
}