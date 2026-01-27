#pragma once
#include "sdl3.hpp"

#include <string_view>
#include <vector>

namespace map
{
    /// @brief Forward.
    class Tileset;

    /// @brief Shared definition.
    using SharedTileset = std::shared_ptr<Tileset>;

    /// @brief Tileset class.
    class Tileset final
    {
        public:
            /// @brief Loads the tileset from the path passed.
            /// @param tileset Path to load the tile set from.
            Tileset(std::string_view tileset);

            /// @brief Loads and creates the tile set from the texture passed.
            /// @param tileset Texture to create the tileset from.
            Tileset(sdl3::SharedTexture tileset);

            /// @brief Inline creation function.
            static inline SharedTileset create(std::string_view tileset) { return std::make_shared<Tileset>(tileset); }

            /// @brief Inline creation function.
            static inline SharedTileset create(sdl3::SharedTexture tileset) { return std::make_shared<Tileset>(tileset); }

            /// @brief Returns the total number of tiles in the set.
            int get_total_tiles() const noexcept;

            /// @brief Renders the tile from the set according to the index it was assigned.
            /// @param index Index of the tile to render.
            void render_tile_by_index(int x, int y, int index);

            /// @brief Renders the tile index stretched to the coordinates passed.
            void render_tile_stretched_by_index(int x, int y, int width, int height, int index);

        private:
            /// @brief Texture being used as a tile set.
            sdl3::SharedTexture m_tileset{};

            /// @brief Vector of tile coordinates for rendering.
            std::vector<std::pair<int, int>> m_tiles{};

            /// @brief Inits the tileset using the texture loaded.
            void initialize_tileset();
    };
}