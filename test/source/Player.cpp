#include "Player.hpp"

#include "Bullet.hpp"
#include "Game.hpp"
#include "screen.hpp"

#include <cmath>
#include <iostream>
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

void Player::update(Game &game, const Input &input)
{
    // Offsets for spawning the bullet.
    static constexpr int BULLET_OFFSET_X = 42;
    static constexpr int BULLET_OFFSET_Y = 16;

    // This is for up and down.
    static constexpr int STATIC_MOVEMENT = 4;

    // Keyboard and pad references.
    const sdl3::Keyboard &keyboard = input.keyboard;

    // Grab keystates.
    bool moveUp      = keyboard.pressed(SDL_SCANCODE_UP) || keyboard.held(SDL_SCANCODE_UP);
    bool moveDown    = keyboard.pressed(SDL_SCANCODE_DOWN) || keyboard.held(SDL_SCANCODE_DOWN);
    bool moveLeft    = keyboard.pressed(SDL_SCANCODE_LEFT) || keyboard.held(SDL_SCANCODE_LEFT);
    bool moveRight   = keyboard.pressed(SDL_SCANCODE_RIGHT) || keyboard.held(SDL_SCANCODE_RIGHT);
    bool spawnBullet = keyboard.pressed(SDL_SCANCODE_SPACE);

    // Only try pad if it's found!.
    const auto padReference = input.gamepads.get_pad_by_index(0);
    if (padReference.has_value())
    {
        // Get this so my hand gets a break.
        const sdl3::Gamepad &pad = padReference->get();

        // Modify values set previously.
        moveUp |= pad.button_pressed(SDL_GAMEPAD_BUTTON_DPAD_UP) || pad.button_held(SDL_GAMEPAD_BUTTON_DPAD_UP);
        moveDown |= pad.button_pressed(SDL_GAMEPAD_BUTTON_DPAD_DOWN) || pad.button_held(SDL_GAMEPAD_BUTTON_DPAD_DOWN);
        moveLeft |= pad.button_pressed(SDL_GAMEPAD_BUTTON_DPAD_LEFT) || pad.button_held(SDL_GAMEPAD_BUTTON_DPAD_LEFT);
        moveRight |= pad.button_pressed(SDL_GAMEPAD_BUTTON_DPAD_RIGHT) || pad.button_held(SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
        spawnBullet |= pad.button_pressed(SDL_GAMEPAD_BUTTON_SOUTH);
    }

    if (moveUp) { m_y -= STATIC_MOVEMENT; }
    else if (moveDown) { m_y += STATIC_MOVEMENT; }

    if (moveLeft) { m_x -= 2; }
    else if (moveRight) { m_x += STATIC_MOVEMENT; }

    if (spawnBullet) { game.create_add_object<Bullet>(m_x + BULLET_OFFSET_X, m_y + BULLET_OFFSET_Y); }

    Player::check_for_collisions(game);
}

void Player::render(Game &game, sdl3::Renderer &renderer) { m_sprite->render(m_x, m_y); }

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