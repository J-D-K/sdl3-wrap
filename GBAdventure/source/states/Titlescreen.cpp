#include "states/Titlescreen.hpp"

#include "graphics/colors.hpp"
#include "graphics/font.hpp"
#include "objects/DialogFrame.hpp"
#include "window.hpp"

#include <array>
#include <string_view>

namespace
{
    /// @brief The title of our adventure game.
    constexpr std::string_view GAME_TITLE = "GB Adventure";
}

//                      ---- Construction ----

states::Titlescreen::Titlescreen()
    : m_font{sdl3::FontManager::load_resource(graphics::font::FONT_PATH, graphics::font::FONT_PATH, graphics::font::FONT_SIZE)}
{
    // Dialog frame width and height.
    static constexpr int DIALOG_WIDTH  = 64;
    static constexpr int DIALOG_HEIGHT = 32;

    // Options for the menu.
    static constexpr std::array<std::string_view, 2> MENU_OPTIONS = {"New Game", "Continue"};

    // Get the width of the title.
    const size_t titleWidth = m_font->get_text_width(GAME_TITLE);

    // Center it.
    m_titleX = window::calculate_centered_horizontal(titleWidth);

    // Centered dialog coordinates.
    const int dialogX = window::calculate_centered_horizontal(DIALOG_WIDTH);

    // Create dialog frame.
    m_objects.create_new_object<objects::DialogFrame>(dialogX, 96, DIALOG_WIDTH, DIALOG_HEIGHT);

    // Menu.
    m_menu = m_objects.create_new_object<objects::Menu>(dialogX + 6, 100, std::span<const std::string_view>(MENU_OPTIONS));
}

//                      ---- Public Functions ----

void states::Titlescreen::update(const sdl3::Input &input)
{
    for (objects::SharedObject &object : m_objects) { object->update(input); }
}

void states::Titlescreen::render(sdl3::Renderer &renderer)
{
    m_font->render_text(m_titleX, 16, graphics::palette::DARK, GAME_TITLE);

    for (objects::SharedObject &object : m_objects) { object->render(renderer); }
}