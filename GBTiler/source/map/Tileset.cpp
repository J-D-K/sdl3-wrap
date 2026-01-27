#include "map/Tileset.hpp"

namespace
{
    constexpr int TILE_SIZE = 16;
}

//                      ---- Construction ----

map::Tileset::Tileset(std::string_view tileset)
    : m_tileset{sdl3::TextureManager::load_resource(tileset, tileset)}
{
    Tileset::initialize_tileset();
}

map::Tileset::Tileset(sdl3::SharedTexture tileset)
    : m_tileset{tileset}
{
    Tileset::initialize_tileset();
}

//                      ---- Public Functions ----

int map::Tileset::get_total_tiles() const noexcept { return m_tiles.size(); }

void map::Tileset::render_tile_by_index(int x, int y, int index)
{
    if (index < 0 || index >= m_tiles.size()) { return; }

    // Bind the coordinates.
    const auto &[tileX, tileY] = m_tiles.at(index);

    // Render the tile.
    m_tileset->render_part(x, y, tileX, tileY, TILE_SIZE, TILE_SIZE);
}

void map::Tileset::render_tile_stretched_by_index(int x, int y, int width, int height, int index)
{
    if (index < 0 || index >= m_tiles.size()) { return; }

    const auto &[tileX, tileY] = m_tiles.at(index);

    m_tileset->render_part_stretched(x, y, width, height, tileX, tileY, TILE_SIZE, TILE_SIZE);
}

//                      ---- Private Functions ----

void map::Tileset::initialize_tileset()
{
    // No calling the get functions over and over.
    const int setWidth  = m_tileset->get_width();
    const int setHeight = m_tileset->get_height();

    // Loop.
    for (int y = 0; y < setHeight; y += TILE_SIZE)
    {
        for (int x = 0; x < setWidth; x += 16) { m_tiles.push_back(std::make_pair(x, y)); }
    }
}