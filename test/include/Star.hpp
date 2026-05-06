#pragma once
#include "Object.hpp"

/// @brief This is more of a scenery thing I thought would look cool.
class Star final : public Object
{
    public:
        /// @brief Initializes the star.
        Star();

        /// @brief Update routine. Moves the star.
        void update(Game &game, const sdl3::Keyboard &keyboard) override;

        /// @brief Renders the star.
        void render(Game &game, sdl3::Renderer &renderer) override;
};