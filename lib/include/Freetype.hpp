#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace sdl3
{
    // Simple container class for Freetype.
    class Freetype final
    {
        public:
            // No copying or moving.
            Freetype(const Freetype &)            = delete;
            Freetype(Freetype &&)                 = delete;
            Freetype &operator=(const Freetype &) = delete;
            Freetype &operator=(Freetype &&)      = delete;

            /// @brief Constructor. Initializes library.
            Freetype()
            {
                if (!m_library) { FT_Init_FreeType(&m_library); }
            }

            /// @brief Destructor needs to be public.
            ~Freetype()
            {
                if (m_library) { FT_Done_FreeType(m_library); }
            }

            /// @brief Returns the freetype library.
            FT_Library get_library() const noexcept { return m_library; }

        private:
            /// @brief Freetype library.
            FT_Library m_library{};
    };
}