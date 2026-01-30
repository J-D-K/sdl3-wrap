#include "ui/MenuBar.hpp"

#include "ui/colors.hpp"
#include "ui/menudims.hpp"
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
    renderer.render_fill_rect(m_x, m_y, renderer.get_width(), 20, ui::colors::MENU);

    // Render the actual menus.
    for (auto &menu : m_menus) { menu->render(renderer); }
}

std::unique_ptr<ui::Menu> &ui::MenuBar::create_add_menu(std::string_view label)
{
    // Create new menu.
    m_menus.push_back(std::make_unique<ui::Menu>(label));

    // Reference for changes.
    auto &menu = m_menus.back();

    menu->m_x      = m_currentX;
    menu->m_labelX = menu->m_x + ((menu->m_width / 2) - (menu->m_labelWidth / 2));

    // Increase the current X and add some margin.
    m_currentX += menu->m_width + ui::menudims::MARGIN;

    return menu;
}
