#pragma once
#include "Object.hpp"

class Enemy final : public Object
{
    public:
        // clang-format off
        /// @brief Struct for storing enemy data in the array.
        struct EnemyData
        {
            const std::string_view spritePath{};
            const int hits{};
            const int speed{};
            const int pointValue{};
        };
        // clang-format on

        /// @brief Initializes the enemy using the table inside the source file.
        Enemy();

        /// @brief Enemy update routine.
        void update(Game &game, const sdl3::Input &input) override;

        /// @brief Enemy render routine.
        void render(Game &game, sdl3::Renderer &renderer) override;

    private:
        /// @brief Number of shots required to destroy the plane.
        int m_hits{};

        /// @brief Speed. This is pulled from the enemy table.
        int m_speed{};

        /// @brief Pointer to the enemy data for the enemy.
        const EnemyData *m_data{};

        /// @brief Font used to render hit count above the enemy.
        static inline sdl3::SharedFont sm_debugFont{};

        /// @brief Checks for collisions with bullet instances.
        /// @param game Reference to game.
        void check_for_bullet_collisions(Game &game) noexcept;

        /// @brief Initializes the font.
        void initialize_static_members();
};