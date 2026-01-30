#include "map/Tile.hpp"

#include "map/tilesize.hpp"
#include "util/is_within.hpp"

//                      ---- Construction ----

map::Tile::Tile(int x, int y)
    : m_x{x}
    , m_y{y} {};

//                      ---- Public Functions ----

void map::Tile::update(const sdl3::Input &input, int index)
{
    // Grab mouse coordinates.
    const int mouseX    = input.get_mouse_x();
    const int mouseY    = input.get_mouse_y();
    const bool isWithin = util::is_within(mouseX, mouseY, m_x, m_y, map::tilesize::TILE_WIDTH, map::tilesize::TILE_HEIGHT);

    // Grab mouse buttons.
    const bool leftClick  = input.get_mouse_button_state(sdl3::Input::MouseButton::Left) == sdl3::Input::State::Pressed;
    const bool rightClick = input.get_mouse_button_state(sdl3::Input::MouseButton::Right) == sdl3::Input::State::Pressed;

    // Conditions.
    const bool changeToIndex = isWithin && leftClick;
    const bool resetToZero   = isWithin && rightClick;

    if (changeToIndex) { m_index = index; }
    else if (resetToZero) { m_index = 0; }
}

void map::Tile::render(map::SharedTileset &tileset) { tileset->render_tile_by_index(m_x, m_y, m_index); }