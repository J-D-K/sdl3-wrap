#pragma once

#include "CoreComponent.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace sdl3
{
    /// @brief This will prevent headaches later.
    class Font;

    /// @brief Freetype wrapper class.
    class Freetype final : public sdl3::CoreComponent
    {
        public:
            // No copying or moving.
            Freetype(const Freetype &)            = delete;
            Freetype(Freetype &&)                 = delete;
            Freetype &operator=(const Freetype &) = delete;
            Freetype &operator=(Freetype &&)      = delete;

            /// @brief Constructor. Initializes Freetype.
            Freetype()
            {
                if (m_library) { return; }
                const FT_Error initError = FT_Init_FreeType(&m_library);
                if (initError != 0) { return; }

                m_isInitialized = true;
            }

            /// @brief Exits Freetype.
            ~Freetype()
            {
                if (!m_library) { return; }

                FT_Done_FreeType(m_library);
            }

            /// @brief Allows font to access the library.
            friend class Font;

        private:
            /// @brief Freetype library.
            FT_Library m_library{};
    };
}