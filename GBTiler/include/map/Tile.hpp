#pragma once
#include "sdl3.hpp"

namespace map
{
    class Tile final
    {
        public:
            /// @brief Tile constructor.
            Tile(int x, int y);

            /// @brief Returns whether or not the tile was clicked.
            bool is_clicked(const sdl3::Input &input) const noexcept
            {
                // Mouse coordinates.
                const int mouseX = input.get_mouse_x();
                const int mouseY = input.get_mouse_y();
            }

            void set_index(int index) noexcept;
    };
}