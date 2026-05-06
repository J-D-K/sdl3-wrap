#include "Bullet.hpp"

#include "Game.hpp"
#include "screen.hpp"

namespace
{
    constexpr int BULLET_SPEED = 8;
}

//                      ---- Construction ----

Bullet::Bullet(int x, int y)
    : Object(Object::Type::Bullet)
{
    // Depth depth above all else, except for player.
    m_depth = -9;

    // Set X and Y.
    m_x = x;
    m_y = y;

    // Load sprite.
    Bullet::load_sprite();
}

//                      ---- Public Functions ----

void Bullet::update(Game &game, const sdl3::Keyboard &keyboard)
{
    // Increase the x.
    m_x += BULLET_SPEED;

    // Mark for purging if off screen.
    if (m_x > LOGICAL_WIDTH) { Object::mark_for_purge(); }
}

void Bullet::render(Game &game, sdl3::Renderer &renderer) { m_sprite->render(m_x, m_y); }

//                      ---- Private Functions ----

void Bullet::load_sprite()
{
    static constexpr std::string_view SPRITE_PATH = "./assets/BulletA.png";
    if (m_sprite) { return; }

    // Load sprite.
    m_sprite = sdl3::TextureManager::load_resource(SPRITE_PATH, SPRITE_PATH);

    // Set width and height.
    m_width  = m_sprite->get_width();
    m_height = m_sprite->get_height();
}
