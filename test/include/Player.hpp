#pragma once
#include "Object.hpp"

class Player final : public Object
{
    public:
        /// @brief Constructor. Ensures player texture is loaded.
        Player();

        /// @brief Runs the update/control routine.
        void update(Game &game, const Input &input) override;

        /// @brief Renders the player sprite to screen.
        void render(Game &game, sdl3::Renderer &render) override;

    private:
        /// @brief Number of ticks before the player's collision kicks in.
        static constexpr uint64_t INVINCIBILITY_TICKS = 3000;

        /// @brief Timer for allowing collision.
        sdl3::Timer m_invinciTimer{INVINCIBILITY_TICKS};

        /// @brief Whether or not the player is solid yet.
        bool m_isSolid{};

        /// @brief Loads the player's texture.
        void load_player_texture();

        /// @brief Checks for collisions.
        void check_for_collisions(Game &game) noexcept;
};