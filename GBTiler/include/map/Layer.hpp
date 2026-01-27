#pragma once
#include "map/"
#include "map/Tileset.hpp"

#include <vector>

namespace map
{
    /// @brief Map layer class.
    class Layer final
    {
        public:
            /// @brief Map layer constructor.
            /// @param columns Number of 16 pixel wide columns.
            /// @param rows Number of 16 pixel tall rows.
            Layer(map::SharedTileset tileset, int columns, int rows);

            /// @brief Updates the tiles in the map layer.
            /// @param input Reference to SDL3 input instance.
            void update(const sdl3::Input &input);

            /// @brief Renders the map.
            void render();

        private:
            // clang-format off
            struct Tile
            {
                int x{};
                int y{};
                int index{};
            };
            // clang-format on 

            /// @brief Vector containing the tiles for the layer.
            std::vector<Tile> m_tiles{};

            /// @brief Shared pointer to the tileset.
            map::SharedTileset m_tileset{};
    };
}