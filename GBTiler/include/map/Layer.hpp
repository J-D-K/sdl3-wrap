#pragma once
#include "map/"
#include "map/Tile.hpp"
#include "map/Tileset.hpp"
#include "sdl3.hpp"

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
            Layer(int columns, int rows);

            /// @brief Updates the tiles in the map layer.
            /// @param input Reference to SDL3 input instance.
            /// @param index Index of the current selected tile.
            void update(const sdl3::Input &input, int index);

            /// @brief Renders the map layer.
            /// @param tileset Reference to shared tileset to render the layer with.
            void render(map::SharedTileset &tileset);

        private:
            /// @brief Vector containing the tiles for the layer.
            std::vector<map::Tile> m_tiles{};

            /// @brief Render target to render the layer to.
            sdl3::SharedTexture m_layerBuffer{};
    };
}