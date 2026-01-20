#include "Player.hpp"

#include "Bullet.hpp"
#include "Game.hpp"
#include "screen.hpp"

#include <cmath>
//                      ---- Construction ----

Player::Player()
    : Object{Object::Type::Player}
{
    // Set the depth so the player is always on top.
    Object::m_depth = -10;

    // Load the sprite.
    Player::load_player_texture();

    // Set the y of the player to be centered.
    m_y = (LOGICAL_HEIGHT / 2) - (m_width / 2);
}

//                      ---- Public Functions ----

void Player::update(Game &game, const sdl3::Input &input)
{
    // This is to make the conditions easier to read.
    using sdl3::Input;
    using sdl3::Input::State::Held;
    using sdl3::Input::State::Pressed;

    // Offsets for spawning the bullet.
    static constexpr int BULLET_OFFSET_X = 42;
    static constexpr int BULLET_OFFSET_Y = 16;

    // This is for up and down.
    static constexpr int STATIC_MOVEMENT = 4;

    // Grab keystates.
    const Input::State upState    = input.get_key_state(SDL_SCANCODE_UP);
    const Input::State downState  = input.get_key_state(SDL_SCANCODE_DOWN);
    const Input::State leftState  = input.get_key_state(SDL_SCANCODE_LEFT);
    const Input::State rightState = input.get_key_state(SDL_SCANCODE_RIGHT);
    const Input::State spaceState = input.get_key_state(SDL_SCANCODE_SPACE);

    // Conditions.
    const bool moveUp      = (upState == Pressed || upState == Held) && m_y > 0;
    const bool moveDown    = (downState == Pressed || downState == Held) && m_y < LOGICAL_WIDTH;
    const bool moveLeft    = (leftState == Pressed || leftState == Held) && m_x > 0;
    const bool moveRight   = (rightState == Pressed || rightState == Held) && m_x < LOGICAL_HEIGHT;
    const bool spawnBullet = spaceState == Pressed;

    if (moveUp) { m_y -= STATIC_MOVEMENT; }
    else if (moveDown) { m_y += STATIC_MOVEMENT; }

    if (moveLeft) { m_x -= 2; }
    else if (moveRight) { m_x += STATIC_MOVEMENT; }

    if (spawnBullet) { game.create_add_object<Bullet>(m_x + BULLET_OFFSET_X, m_y + BULLET_OFFSET_Y); }

    Player::check_for_collisions(game);
}

void Player::render() { m_sprite->render(m_x, m_y); }

//                      ---- Private Functions ----

void Player::load_player_texture()
{
    static constexpr std::string_view PLAYER_TEXTURE_PATH = "./assets/PlayerA.png";

    if (m_sprite) { return; }

    // Load the sprite.
    m_sprite = sdl3::TextureManager::load_resource(PLAYER_TEXTURE_PATH, PLAYER_TEXTURE_PATH);

    // Store the width and height.
    m_width  = m_sprite->get_width();
    m_height = m_sprite->get_height();
}

void Player::check_for_collisions(Game &game) noexcept
{
    // Point hit.
    static constexpr int POINT_DEDUCTION = -500;

    // Span.
    std::span<const UniqueObject> objects = game.get_game_objects();

    // Loop.
    for (const UniqueObject &object : objects)
    {
        const bool isEnemy = object->get_type() == Object::Type::Enemy;

        if (isEnemy && Object::collision(object))
        {
            // Mark this instance as purgable.
            Object::mark_for_purge();

            // "Respawn."
            game.create_add_object<Player>();

            // Deduct points as punishment.
            game.add_to_score(POINT_DEDUCTION);
        }
    }
}