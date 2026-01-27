#include "map/Layer.hpp"

//                      ---- Construction ----

map::Layer::Layer(map::SharedTileset tileset, int columns, int rows)
    : m_tileset(tileset)
{
    static constexpr int TILE_SIZE = 16;

    // Number of tiles to create.
    const int tileCount = columns * rows;

    // Loop and create the tiles.
    for (int i = 0, y = 0; i < rows; i++, y += 16)
    {
        for (int j = 0, x = 0; j < columns; j++, x += 16)
        {
            // New tile to push back.
            const Tile newTile = {.x = x, .y = y, .index = 0};
            m_tiles.push_back(newTile);
        }
    }
}

//                      ---- Public Functions ----

void map::Layer::update(const sdl3::Input &input) {}