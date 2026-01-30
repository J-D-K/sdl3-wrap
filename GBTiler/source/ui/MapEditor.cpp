#include "ui/MapEditor.hpp"

#include "map/tilesize.hpp"
#include "sdl3.hpp"
#include "ui/colors.hpp"
#include "window.hpp"

#include <string_view>

namespace
{
    // Number of layers. This is limited to two to be more gameboy-like.
    static constexpr int MAP_LAYERS = 2;

    /// @brief Name of the target.
    static constexpr std::string_view MAP_TARGET_NAME = "TilemapTarget";
}

//                      ---- Construction ----

ui::MapEditor::MapEditor(map::SharedTileset tileset, int columns, int rows)
    : m_tileset{tileset}
    , m_mapTarget{sdl3::TextureManager::load_resource(MAP_TARGET_NAME,
                                                      columns * map::tilesize::TILE_WIDTH,
                                                      rows * map::tilesize::TILE_HEIGHT,
                                                      SDL_TEXTUREACCESS_TARGET)}
    , m_mapX{(window::WIDTH / 2) - (m_mapTarget->get_width() / 2)}
    , m_mapY{(window::HEIGHT / 2) - (m_mapTarget->get_height() / 2)}
{
    // Init the map layers.
    for (int i = 0; i < MAP_LAYERS; i++) { m_layers.emplace_back(columns, rows); }
}

//                      ---- Public Functions ----

void ui::MapEditor::update(const sdl3::Input &input)
{
    // Bail if this occurs.
    if (m_layer < 0 || m_layer >= MAP_LAYERS) { return; }

    // Store this for later.
    const int totalTiles = m_tileset->get_total_tiles();

    // Get up and down.
    const bool upPressed   = input.get_key_state(SDL_SCANCODE_UP) == sdl3::Input::State::Pressed;
    const bool downPressed = input.get_key_state(SDL_SCANCODE_DOWN) == sdl3::Input::State::Pressed;

    // Switch index.
    if (upPressed) { --m_index; }
    else if (downPressed) { ++m_index; }

    // Handle over and under flowing index.
    if (m_index < 0) { m_index = totalTiles - 1; }
    else if (m_index >= totalTiles) { m_index = 0; }

    // Update the current layer.
    m_layers.at(m_layer).update(input, m_index);
}

void ui::MapEditor::render(sdl3::Renderer &renderer)
{
    // Change render target to map target.
    renderer.set_render_target(m_mapTarget);

    // Clear to black.
    renderer.clear(ui::colors::BLACK);

    // Loop and render the layers.
    for (map::Layer &layer : m_layers) { layer.render(m_tileset); }

    // Set back to main render target.
    renderer.set_render_target(sdl3::Texture::NullTexture);

    // Render the final map to the target.
    m_mapTarget->render(m_mapX, m_mapY);
}