#pragma once
#include "map/Tileset.hpp"
#include "sdl3.hpp"

namespace map
{
    class Tile final
    {
        public:
            /// @brief Tile constructor.
            Tile(int x, int y);

            /// @brief Update routine.
            /// @param input Reference to input instance.
            /// @param index Index of the currently selected tile.
            void update(const sdl3::Input &input, int index);

            /// @brief Render routine. Renders the tile to the currently selected render target.
            /// @param tileset Reference to tileset to use to render the tile from.
            void render(map::SharedTileset &tileset);

        private:
            /// @brief X render coordinate.
            int m_x{};

            /// @brief Y render coordinate.
            int m_y{};

            /// @brief Index of the tile in the tileset.
            int m_index{};
    };
}