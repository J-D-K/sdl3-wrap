#pragma once
#include "Object.hpp"

class Bullet final : public Object
{
    public:
        /// @brief Initializes the bullet.
        /// @param x X position of the bullet.
        /// @param y Y position of the bullet.
        Bullet(int x, int y);

        /// @brief Runs the bullet update routine.
        void update(Game &game, const sdl3::Input &input) override;

        /// @brief Renders the pellet to screen.
        void render();

    private:
        /// @brief Loads the sprite if it hasn't been already.
        void load_sprite();

        /// @brief Checks for collisions with objects.
        void check_for_collisions(Game &game) noexcept;
};