#pragma once
#include "Object.hpp"

class Player final : public Object
{
    public:
        /// @brief Constructor. Ensures player texture is loaded.
        Player();

        /// @brief Runs the update/control routine.
        void update(Game &game, const sdl3::Input &input) override;

        /// @brief Renders the player sprite to screen.
        void render() override;

    private:
        /// @brief Loads the player's texture.
        void load_player_texture();

        /// @brief Checks for collisions.
        void check_for_collisions(Game &game) noexcept;
};