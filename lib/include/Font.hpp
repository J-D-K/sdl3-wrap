#pragma once

#include "OptionalReference.hpp"
#include "Texture.hpp"

#include <ft2build.h>
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>
#include FT_FREETYPE_H

// The code here is based on the freetype tutorial.
namespace sdl3
{
    /// @brief Forward declaration for sweet tricks.
    class Font;

    /// @brief Makes stuff easier to type.
    using SharedFont = std::shared_ptr<sdl3::Font>;

    /// @brief This is a wrapper class around SDL3 and Freetype. It's not the most efficient, but it works.
    class Font final
    {
        public:
            // clang-format off
            /// @brief Struct for cacheing glyph data for the map.
            struct GlyphData
            {
                int16_t advanceX{};
                int16_t top{};
                int16_t left{};
                sdl3::SharedTexture texture{};
            };
            // clang-format on

            /// @brief Default constructor.
            Font() = default;

            /// @brief Loads the font from the path passed.
            /// @param fontPath Path of the font to load.
            /// @param pixelSize Size of the font in pixels.
            Font(std::string_view fontPath, int pixelSize);

            /// @brief Frees the Freetype face.
            ~Font();

            /// @brief Renders text to the target using the font.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param renderColor Color to render mod and render the text with.
            /// @param text Text to render.
            void render_text_to(int x, int y, SDL_Color renderColor, std::string_view text);

            /// @brief Renders the text wrapped to the target using the arguments passed.
            /// @param target Target to render text to.
            /// @param x X coordinate to render text to.
            /// @param y Y coordinate to render text to.
            /// @param maxWidth Maximum width of the text before a new line is started.
            /// @param renderColor Color to render text with.
            /// @param text Text to render.
            void render_text_to_wrapped(int x, int y, int maxWidth, SDL_Color renderColor, std::string_view text);

            /// @brief Returns the width of the string in pixels.
            /// @param text Text to get the width of.
            /// @return Width of the text in pixels.
            size_t get_text_width(std::string_view text);

        private:
            /// @brief Stores whether or not loading the font was successful.
            bool m_isValid{};

            /// @brief Size of the glyphs in pixels.
            int m_pixelSize{};

            /// @brief Font face used.
            FT_Face m_fontFace{};

            /// @brief Buffer for storing the font in RAM. This makes accessing it faster.
            std::unique_ptr<char[]> m_fontBuffer{};

            /// @brief Glyphs mapped to their char for quick searching and retrieval.
            std::unordered_map<char, Font::GlyphData> m_cacheMap{};

            /// @brief Attempts to find the glyph for the character passed. If that fails, it's loaded using freetype.
            /// @param charCode Character to search for or load.
            /// @return Pointer to cached glyph data on success. nullptr on failure.
            sdl3::OptionalReference<Font::GlyphData> find_load_glyph(char charCode);

            /// @brief Takes the bitmap passed, blits it to a surface, and then returns it as an SDL texture.
            /// @param glyphBitmap Bitmap to convert.
            /// @return Shared texture containing the glyph, nullptr on failure.
            sdl3::SharedTexture convert_glyph_to_texture(char charCode, const FT_Bitmap glyphBitmap);
    };
}