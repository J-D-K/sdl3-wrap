#pragma once

namespace util
{
    /// @brief Returns if the X and Y passed are within the area passed.
    /// @param x X to check.
    /// @param y Y to check.
    /// @param areaX X of the area to check.
    /// @param areaY Y of the area to check.
    /// @param areaWidth Width of the area to check.
    /// @param areaHeight Height of the area to check.
    /// @return True if the X and Y are within the area, false if not.
    inline bool is_within(int x, int y, int areaX, int areaY, int areaWidth, int areaHeight)
    {
        // Checking if it's outside and inverting the results are actually easier.
        const bool outsideX = x < areaX || x > areaX + areaWidth;
        const bool outsideY = y < areaY || y > areaY + areaHeight;

        return !outsideX && !outsideY;
    }
}