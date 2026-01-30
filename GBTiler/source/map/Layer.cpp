#include "map/Layer.hpp"

namespace
{
    constexpr int TILE_SIZE = 16;
}

//                      ---- Construction ----

map::Layer::Layer(map::SharedTileset tileset, int columns, int rows)
    : m_tileset(tileset)
{
    // Number of tiles to create.
    const int tileCount = columns * rows;

    // Loop and create the tiles.
    for (int i = 0, y = 0; i < rows; i++, y += 16)
    {
        for (int j = 0, x = 0; j < columns; j++, x += 16) { m_tiles.emplace_back(x, y, m_tileset); }
    }
}

//                      ---- Public Functions ----

void map::Layer::update(const sdl3::Input &input, int index)
{
    for (map::Tile &tile : m_tiles) { tile.update(input, index); }
}

void map::Layer::render(sdl3::Renderer &renderer) {}

//                      ---- Private Functions ----
