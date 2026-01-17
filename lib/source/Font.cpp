#include "Font.hpp"

#include "Freetype.hpp"
#include "ResourceManager.hpp"
#include "Surface.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <span>

//                      ---- Construction ----

sdl3::Font::Font(std::string_view fontPath, int pixelSize)
    : m_pixelSize{pixelSize}
{
    // Attempt to get the file size of the font.
    const size_t fontSize = std::filesystem::file_size(fontPath);
    if (fontSize == 0) { return; }

    // Buffer for the font.
    m_fontBuffer = std::make_unique<char[]>(fontSize);
    if (!m_fontBuffer) { return; }

    // Open the font for reading.
    std::ifstream fontFile{fontPath.data(), std::ios::binary};
    if (!fontFile.is_open()) { return; }

    // Read it to buffer.
    fontFile.read(m_fontBuffer.get(), fontSize);
    if (fontFile.gcount() != fontSize) { return; }

    // Create the font face.
    FT_Error ftError =
        FT_New_Memory_Face(Freetype::get_library(), reinterpret_cast<FT_Byte *>(m_fontBuffer.get()), fontSize, 0, &m_fontFace);
    if (ftError != 0) { return; }

    // Set the size.
    ftError = FT_Set_Pixel_Sizes(m_fontFace, 0, m_pixelSize);
    if (ftError != 0) { return; }

    m_isValid = true;
}

sdl3::Font::~Font()
{
    if (!m_fontFace) { return; }

    FT_Done_Face(m_fontFace);
}

//                      ---- Public Functions ----

void sdl3::Font::render_text_to(int x, int y, SDL_Color renderColor, std::string_view text)
{
    // Store this because we might need it.
    const int originalX = x;

    // Loop through the text and render it.
    for (const char charCode : text)
    {
        // Handle newlines here instead of processing them after the glyph is loaded.
        if (charCode == '\n')
        {
            x = originalX;
            y += m_pixelSize + (m_pixelSize / 4);
            continue;
        }

        // Try to load the glyph first.
        const auto getGlyph = Font::find_load_glyph(charCode);
        if (!getGlyph.has_value()) { continue; } // If the optional is empty, just continue the loop.

        // Data reference to make things easier to type and read.
        const Font::GlyphData &glyphData = getGlyph->get();

        // Set the color mod.
        glyphData.texture->set_color_mod(renderColor);

        // Render the glyph.
        const int renderX = x + glyphData.left;
        const int renderY = y + (m_pixelSize - glyphData.top);
        glyphData.texture->render(renderX, renderY);

        // Advance our rendering position.
        x += glyphData.advanceX;
    }
}

void sdl3::Font::render_text_to_wrapped(int x, int y, int maxWidth, SDL_Color renderColor, std::string_view text)
{
    // Save this just in case.
    const int originalX = x;

    // This is our adjusted maxWidth.
    const int adjustedMax = x + maxWidth;

    // This is our current width.
    size_t currentWidth{};

    // This is different than the above because we need to track the length differently.
    const size_t textLength = text.length();

    // This is so I don't have to repeat this.
    auto break_line = [&]()
    {
        x = originalX;
        y += m_pixelSize + (m_pixelSize / 4);
    };

    // Loop through text.
    for (size_t i = 0; i < textLength;)
    {
        // Find the next valid breakpoint and create a substring. Even if this is npos, it will work.
        size_t nextBreakpoint = text.find_first_of(" .", i);
        if (nextBreakpoint != text.npos) { ++nextBreakpoint; }
        std::string_view word{text.substr(i, nextBreakpoint - i)};

        // Get the length of the word. If we've surpassed our max, break the line.
        const size_t wordWidth = Font::get_text_width(word);
        if (x + wordWidth >= adjustedMax) { break_line(); }

        // Loop through the word and render it.
        for (const char charCode : word)
        {
            // Line breaking.
            if (charCode == '\n')
            {
                break_line();
                continue;
            }

            // Try to load/find the glyph. If it's not found, just continue.
            const auto getGlyph = Font::find_load_glyph(charCode);
            if (!getGlyph.has_value()) { continue; }

            // Get the actual data.
            const Font::GlyphData &glyphData = getGlyph->get();

            // Render color.
            glyphData.texture->set_color_mod(renderColor);

            // Render the glyph.
            const int renderX = x + glyphData.left;
            const int renderY = y + (m_pixelSize - glyphData.top);
            glyphData.texture->render(renderX, renderY);

            // Advance position.
            x += glyphData.advanceX;
        }

        i += word.length();
    }
}

size_t sdl3::Font::get_text_width(std::string_view text)
{
    size_t textWidth{};
    for (const char charCode : text)
    {
        // Ignore line breaks.
        if (charCode == '\n') { continue; }

        // Attempt to get glyph.
        const auto getGlyph = Font::find_load_glyph(charCode);
        if (!getGlyph.has_value()) { continue; }

        // Actual glyph data.
        const Font::GlyphData &glyphData = getGlyph->get();

        // Add the advance to the text width.
        textWidth += glyphData.advanceX;
    }

    return textWidth;
}

//                      ---- Private Functions ----

sdl3::OptionalReference<sdl3::Font::GlyphData> sdl3::Font::find_load_glyph(char charCode)
{
    // Start by searching the map for the character.
    const auto findCharacter = m_cacheMap.find(charCode);
    if (findCharacter != m_cacheMap.end()) { return findCharacter->second; }

    // Check if the character exists in the font.
    const FT_UInt charIndex  = FT_Get_Char_Index(m_fontFace, charCode);
    const FT_Error loadError = FT_Load_Glyph(m_fontFace, charIndex, FT_LOAD_RENDER);
    if (loadError != 0) { return std::nullopt; }

    // This makes things easier to read.
    const FT_GlyphSlot glyphSlot = m_fontFace->glyph;
    const FT_Bitmap glyphBitmap  = glyphSlot->bitmap;

    // Convert to texture.
    sdl3::SharedTexture glyphTexture = Font::convert_glyph_to_texture(charCode, glyphBitmap);

    // Add to cache map.
    // Struct
    Font::GlyphData cacheData = {.advanceX = static_cast<int16_t>(glyphSlot->advance.x >> 6),
                                 .top      = static_cast<int16_t>(glyphSlot->bitmap_top),
                                 .left     = static_cast<int16_t>(glyphSlot->bitmap_left),
                                 .texture  = glyphTexture};

    // Try emplace.
    const auto emplacePair = m_cacheMap.try_emplace(charCode, cacheData);
    if (!emplacePair.second) { return std::nullopt; }

    // Return the one in the cache map since the other was temporary and will die once this function finishes.
    return m_cacheMap.at(charCode);
}

sdl3::SharedTexture sdl3::Font::convert_glyph_to_texture(char charCode, const FT_Bitmap glyphBitmap)
{
    // The base pixel color is white. That makes it easier to color later.
    static constexpr uint32_t BASE_PIXEL_COLOR = 0xFFFFFF00;

    // Bitmap size. I've always found Freetype's rows instead of height confusing.
    const size_t bitmapSize = glyphBitmap.width * glyphBitmap.rows;

    // Temporary surface.
    sdl3::Surface surface = sdl3::create_new_surface_rgba(glyphBitmap.width, glyphBitmap.rows);

    // Cast pointer to raw surface data.
    uint32_t *rawSurface = reinterpret_cast<uint32_t *>(surface.get()->pixels);

    // Spans for blitting. These should both be the same size.
    std::span<uint32_t> surfacePixels{rawSurface, bitmapSize};
    std::span<const uint8_t> bitmapPixels{glyphBitmap.buffer, bitmapSize};

    // Loop and blit.
    for (size_t i = 0; i < bitmapSize; i++) { surfacePixels[i] = BASE_PIXEL_COLOR | bitmapPixels[i]; }

    // Name for the texture manager to keep track.
    const std::string glyphName = std::format("{}-{}", charCode, m_pixelSize);

    // Return the texture. We're going to use a name here instead of a path.
    return sdl3::TextureManager::load_resource(glyphName, surface);
}