#pragma once
#include "map/Layer.hpp"
#include "map/Tileset.hpp"
#include "sdl3.hpp"
#include "ui/Element.hpp"

#include <array>

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
            /// @brief This is the number of layers for the array.
            static constexpr size_t MAP_LAYERS = 2;

            /// @brief Shared tileset.
            map::SharedTileset m_tileset{};

            /// @brief Array of map layers.
            std::array<map::Layer, MAP_LAYERS> m_layers;

            /// @brief Target the map is rendered to.
            sdl3::SharedTexture m_mapTarget{};
    };
}