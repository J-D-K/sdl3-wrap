#include "Game.hpp"

#include "Enemy.hpp"
#include "Player.hpp"
#include "Star.hpp"
#include "screen.hpp"
#include "sdl3.hpp"

#include <algorithm>
#include <cstdlib>
#include <format>
#include <string_view>

namespace
{
    constexpr std::string_view WINDOW_TITLE = "SDL3 Wrapper Test";
}

//                      ---- Construction ----

Game::Game()
    : m_sdl3()
    , m_window{WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT}
    , m_renderer{m_window}
    , m_input{}
{
    // Path of the main font used.
    static constexpr std::string_view FONT_PATH = "./assets/MainFont.ttf";

    // Init texture.
    sdl3::Texture::initialize(m_renderer);

    // Load the font.
    m_font = sdl3::FontManager::load_resource(FONT_PATH, FONT_PATH, 14);

    // Create the player.
    m_objects.push_back(std::make_unique<Player>());
}

//                      ---- Public Functions ----

int Game::run() noexcept
{
    while (true)
    {
        // Pump events.
        m_sdl3.pump_events();

        // Update input.
        m_input.update();

        // Exit on escape.
        const sdl3::Input::State escape = m_input.get_key_state(SDL_SCANCODE_ESCAPE);
        const bool exit                 = escape == sdl3::Input::State::Pressed;
        if (exit) { return 0; }

        // Game update and render.
        Game::update();
        Game::render();
    }
}

std::span<const UniqueObject> Game::get_game_objects() const noexcept { return std::span<const UniqueObject>{m_objects}; }

void Game::add_to_score(int64_t addScore) noexcept { m_score += addScore; }

//                      ---- Private Functions ----

void Game::update() noexcept
{
    // Kill offscreen objects.
    Game::purge_offscreen_objects();

    // Loop and update objects.
    for (auto &object : m_objects) { object->update(*this, m_input); }

    // Roll to spawn enemy. 15% chance.
    const bool spawnEnemy = (std::rand() % 100) <= 3;
    if (spawnEnemy)
    {
        // Push the object back.
        m_objects.push_back(std::make_unique<Enemy>());
    }

    // Re-sort the vector.
    Game::sort_objects_by_depth();
}

void Game::render() noexcept
{
    static constexpr SDL_Color CLEAR = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0x00};

    // Start the rendering process.
    m_renderer.frame_begin(CLEAR);

    // Loop and render objects.
    for (auto &object : m_objects) { object->render(*this, m_renderer); }

    m_font->render_text(0, 0, {0xFF, 0xFF, 0xFF, 0xFF}, std::format("Score: {}\nObject Count: {}", m_score, m_objects.size()));

    m_renderer.frame_end();
}

//                      ---- Private Functions ----

void Game::purge_offscreen_objects()
{
    for (auto iter = m_objects.begin(); iter != m_objects.end();)
    {
        // This is easier to type and read.
        const Object &object = *iter->get();

        if (object.is_purgable())
        {
            iter = m_objects.erase(iter);
            continue;
        }

        // Increment iterator.
        ++iter;
    }
}

void Game::sort_objects_by_depth()
{
    using UniqueObject = std::unique_ptr<Object>;

    // Lambda for sorting.
    auto sortLambda = [](const UniqueObject &a, const UniqueObject &b) { return a->get_depth() > b->get_depth(); };

    // Sort the vector.
    std::sort(m_objects.begin(), m_objects.end(), sortLambda);
}