#include "ui/MenuBar.hpp"

#include "ui/colors.hpp"
#include "window.hpp"

//                      ---- Construction ----

//                      ---- Public Functions ----

void ui::MenuBar::update(const sdl3::Input &input)
{
    for (auto &menu : m_menus) { menu->update(input); }
}

void ui::MenuBar::render(sdl3::Renderer &renderer)
{
    // Render the bar.
    renderer.render_fill_rect(m_x, m_y, window::WIDTH, 20, ui::colors::MENU);

    // Render the actual menus.
    for (auto &menu : m_menus) { menu->render(renderer); }
}

void ui::MenuBar::add_menu(std::unique_ptr<ui::Menu> &menu)
{
    // This is the margin between two menus.
    static constexpr int MENU_MARGIN = 2;

    // Set the coordinates for the new menu.
    menu->m_x      = m_currentX;
    menu->m_labelX = menu->m_x + ((menu->m_width / 2) - (menu->m_labelWidth / 2));

    // Increase our current X.
    m_currentX += menu->m_width + MENU_MARGIN;

    m_menus.push_back(std::move(menu));
}