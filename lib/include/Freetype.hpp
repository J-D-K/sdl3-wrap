#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace sdl3
{
    // This is a small singleton for initializing the global freetype library used to ensure it's exited correctly.
    class Freetype final
    {
        public:
            // No copying or moving.
            Freetype(const Freetype &)            = delete;
            Freetype(Freetype &&)                 = delete;
            Freetype &operator=(const Freetype &) = delete;
            Freetype &operator=(Freetype &&)      = delete;

            /// @brief Destructor needs to be public.
            ~Freetype()
            {
                // Get instance.
                Freetype &instance = Freetype::get_instance();

                // If it's not initialized, bail.
                if (!instance.m_library) { return; }

                FT_Done_FreeType(instance.m_library);
            }

            static bool initialize()
            {
                // Instance.
                Freetype &instance = Freetype::get_instance();

                // Library
                FT_Library *library = &instance.m_library;

                // Init/return
                return FT_Init_FreeType(library) == 0;
            }

            /// @brief Returns the Freetype library.
            static FT_Library get_library() noexcept
            {
                // Instance.
                Freetype &instance = Freetype::get_instance();
                return instance.m_library;
            }

        private:
            /// @brief Freetype library.
            FT_Library m_library{};

            /// @brief Constructor is private.
            Freetype() = default;

            static Freetype &get_instance()
            {
                static Freetype instance{};
                return instance;
            }
    };
}