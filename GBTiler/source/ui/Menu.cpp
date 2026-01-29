#include "ui/Menu.hpp"

#include "ui/colors.hpp"
#include "ui/font.hpp"
#include "ui/menudims.hpp"

//                      ---- Construction ----

ui::Menu::Menu(std::string_view menuName)
    : m_label{menuName}
{
    // Ensure font is loaded.
    Menu::initialize_static_members();

    // Get the width of the label. The final width is the width of the label plus the padding from above.
    m_labelWidth = sm_uiFont->get_text_width(m_label);
    m_width      = m_labelWidth + ui::menudims::PADDING;

    // Set the height and label position.
    m_height = ui::menudims::HEIGHT;
    m_labelY = m_y + ((m_height / 2) - (ui::font::SIZE / 2));

    // Set the sub y.
    m_subY = m_y + ui::menudims::HEIGHT;
}

//                      ---- Public Functions ----

void ui::Menu::add_sub_option(std::string_view label, std::function<void()> onClick)
{
    // Emplace the new sub-option.
    m_subOptions.emplace_back(m_x, m_subY, label, onClick);

    // Run the update routine so the width of all of them match.
    Menu::update_sub_options();

    // Increase our subY
    m_subY += ui::menudims::HEIGHT;

    // Increase our total height.
    m_openHeight += ui::menudims::HEIGHT;
}

void ui::Menu::update(const sdl3::Input &input)
{
    switch (m_state)
    {
        case State::Idle:    Menu::update_idle(input); break;
        case State::Hovered: Menu::update_hover(input); break;
        case State::Clicked: Menu::update_clicked(input); break;
        default:             return;
    }
}

void ui::Menu::render(sdl3::Renderer &renderer)
{
    // Render the back.
    switch (m_state)
    {
        case State::Idle:    Menu::render_idle(renderer); break;
        case State::Hovered: Menu::render_hover(renderer); break;
        case State::Clicked: Menu::render_clicked(renderer); break;
        default:             return;
    }
}

//                      ---- Private Functions ----

void ui::Menu::update_idle(const sdl3::Input &input) noexcept
{
    if (Element::mouse_is_within(input)) { m_state = State::Hovered; }
}

void ui::Menu::update_hover(const sdl3::Input &input) noexcept
{
    // Store whether or not the mouse is still within.
    const bool isWithin = Element::mouse_is_within(input);

    // Whether or not left button was clicked.
    const bool leftClicked = input.get_mouse_button_state(sdl3::Input::MouseButton::Left) == sdl3::Input::State::Pressed;

    // Conditions for state switching.
    const bool idle    = !isWithin;
    const bool clicked = isWithin && leftClicked;

    if (clicked) { m_state = State::Clicked; }
    else if (idle) { m_state = State::Idle; }
}

void ui::Menu::update_clicked(const sdl3::Input &input) noexcept
{
    // Store mouse.
    const int mouseX = input.get_mouse_x();
    const int mouseY = input.get_mouse_y();

    // Mouse buttons.
    const bool leftClick  = input.get_mouse_button_state(sdl3::Input::MouseButton::Left) == sdl3::Input::State::Pressed;
    const bool rightClick = input.get_mouse_button_state(sdl3::Input::MouseButton::Right) == sdl3::Input::State::Pressed;

    // Store whether or not the mouse is outside the main menu.
    const bool isWithinMenu = Element::mouse_is_within(input);
    // This is whether or not it's outside the sub-area.
    const bool isWithinSub = util::is_within(mouseX, mouseY, m_x, m_y + ui::menudims::HEIGHT, m_openWidth, m_openHeight);

    // Conditions
    const bool closeMenu = !isWithinMenu && !isWithinSub && (leftClick || rightClick);

    if (closeMenu) { m_state = State::Idle; }
    else
    {
        for (ui::MenuOption &option : m_subOptions) { option.update(input); }
    }
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

void ui::Menu::render_clicked(sdl3::Renderer &renderer)
{
    // Start by rendering the main menu hovered.
    Menu::render_hover(renderer);

    // Loop and render options.
    for (ui::MenuOption &option : m_subOptions) { option.render(renderer); }
}

void ui::Menu::update_sub_options() noexcept
{
    // Loop and find the largest width.
    for (const ui::MenuOption &option : m_subOptions)
    {
        const int width = option.get_width();
        if (width > m_openWidth) { m_openWidth = width; }
    }

    // Loop and set them all accordingly.
    for (ui::MenuOption &option : m_subOptions) { option.set_width(m_openWidth); }
}

void ui::Menu::render_sub_options(sdl3::Renderer &renderer) noexcept
{
    for (ui::MenuOption &option : m_subOptions) { option.render(renderer); }
}