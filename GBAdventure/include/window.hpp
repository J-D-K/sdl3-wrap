#pragma once
#include <string_view>

namespace window
{
    inline constexpr std::string_view TITLE = "GBAdventure";
    inline constexpr int WIDTH              = 1120;
    inline constexpr int HEIGHT             = 1008;
    inline constexpr int LOGICAL_WIDTH      = 160;
    inline constexpr int LOGICAL_HEIGHT     = 144;

    /// @brief Inline function to return a centered X coordinate according to the width passed.
    /// @param width Width of the item to center.
    inline int calculate_centered_horizontal(int width) { return (window::LOGICAL_WIDTH / 2) - (width / 2); }

    /// @brief Inline function to return a centered Y coordinate according to the height passed.
    /// @param height Height of the item to center.
    inline int calculate_centered_vertical(int height) { return (window::LOGICAL_HEIGHT / 2) - (height / 2); }
}