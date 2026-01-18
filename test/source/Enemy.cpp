#include "Enemy.hpp"

#include "Game.hpp"
#include "screen.hpp"

#include <array>
#include <cstdlib>

namespace
{
    /// @brief Total count of enemies.
    constexpr size_t ENEMY_COUNT = 5;

    // Table for pulling enemy data from.
    constexpr std::array<Enemy::EnemyData, 5> ENEMY_TABLE = {{{"./assets/EnemyA.png", 1, 6, 100},
                                                              {"./assets/EnemyB.png", 3, 4, 300},
                                                              {"./assets/EnemyC.png", 2, 5, 200},
                                                              {"./assets/EnemyD.png", 5, 2, 500},
                                                              {"./assets/EnemyE.png", 4, 3, 400}}};

}

//                      ---- Construction ----

Enemy::Enemy()
    : Object(Object::Type::Enemy)
{
    // Initialize the debug font.
    Enemy::initialize_static_members();

    // Generate a random index for the enemy.
    const int enemyIndex = std::rand() % ENEMY_COUNT;

    // Set the depth to be random, but always positive.
    Object::m_depth = enemyIndex;

    // Grab a reference to it from the array.
    m_data = &ENEMY_TABLE[enemyIndex];

    // Load the sprite.
    m_sprite = sdl3::TextureManager::load_resource(m_data->spritePath, m_data->spritePath);

    // Record width and height.
    m_width  = m_sprite->get_width();
    m_height = m_sprite->get_height();

    // X is always the edge of the screen.
    m_x = LOGICAL_WIDTH + (std::rand() % LOGICAL_WIDTH);

    // Y is random.
    m_y = std::rand() % (LOGICAL_HEIGHT - m_height);

    // Store width and height.
    m_width  = m_sprite->get_width();
    m_height = m_sprite->get_height();

    // Set the number of hits.
    m_hits = m_data->hits;

    // Set the speed.
    m_speed = m_data->speed;
}

//                      ---- Public Functions ----

void Enemy::update(Game &game, const sdl3::Input &input)
{
    // Move to the left and the speed from earlier.
    m_x -= m_speed;

    // Check for bullet collisions.
    Enemy::check_for_bullet_collisions(game);

    // If we're off the edge of the screen, mark as purgable.
    if (m_x + m_width < 0) { m_isPurgable = true; }
}

void Enemy::render()
{
    // Color for rendering hit counts.
    static constexpr SDL_Color GREEN = {.r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF};

    // Debug stuff.
    const std::string hitCount = std::format("HP: {}", m_hits);
    const size_t hitWidth      = sm_debugFont->get_text_width(hitCount);
    const int hitX             = (m_x + (m_width / 2)) - (hitWidth / 2);
    sm_debugFont->render_text(hitX, m_y - 12, GREEN, hitCount);

    m_sprite->render(m_x, m_y);
}

//                      ---- Private Functions ----

void Enemy::check_for_bullet_collisions(Game &game) noexcept
{
    // Get the span of objects.
    std::span<const UniqueObject> objectSpan = game.get_game_objects();

    // Loop through and check for collisions.
    for (const UniqueObject &object : objectSpan)
    {
        // If it's a bullet and there's a collision, add points to score and mark for purge.
        if (object->get_type() == Object::Type::Bullet && Object::collision(object))
        {
            // Decrease hit points.
            --m_hits;

            // Mark the bullet for purge.
            object->mark_for_purge();
        }

        // If we've hit 0 hit points left, add to score, and purge.
        if (m_hits == 0)
        {
            game.add_to_score(m_data->pointValue);
            Object::mark_for_purge();
        }
    }
}

void Enemy::initialize_static_members()
{
    static constexpr std::string_view FONT_NAME = "DebugFont";
    static constexpr std::string_view FONT_PATH = "./assets/MainFont.ttf";
    static constexpr int FONT_SIZE              = 8;

    if (sm_debugFont) { return; }
    sm_debugFont = sdl3::FontManager::load_resource(FONT_NAME, FONT_PATH, FONT_SIZE);
}