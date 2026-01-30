#pragma once
#include "map/Layer.hpp"
#include "map/Tileset.hpp"
#include "sdl3.hpp"
#include "ui/Element.hpp"

#include <vector>

namespace ui
{
    /// @brief This class "contains" the map to a render target.
    class MapEditor final : public ui::Element
    {
        public:
            /// @brief Constructor.
            /// @param columns Number of tile columns. GBAdventure uses 16x16 tiles.
            /// @param rows Number of rows.
            MapEditor(map::SharedTileset tileset, int columns, int rows);

            /// @brief Update override.
            void update(const sdl3::Input &input) override;

            /// @brief Render override.
            void render(sdl3::Renderer &renderer) override;

        private:
            /// @brief Index of the currently selected tile.
            int m_index{};

            /// @brief The layer currently being edited.
            int m_layer{};

            /// @brief Centered render coordinate of the map.
            int m_mapX{};

            /// @brief Centered render coordinate of the map.
            int m_mapY{};

            /// @brief Shared tileset.
            map::SharedTileset m_tileset{};

            /// @brief Vector of layers.
            std::vector<map::Layer> m_layers{};

            /// @brief Target the map is rendered to.
            sdl3::SharedTexture m_mapTarget{};
    };
}