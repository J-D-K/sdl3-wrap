#pragma once
#include "Element.hpp"
#include "sdl3.hpp"
#include "ui/font.hpp"

#include <string>

namespace ui
{
    /// @brief Container for UI text.
    class Text final : public ui::Element
    {
        public:
            Text(int x, int y, SDL_Color color, std::string_view text)
                : Element(x, y)
                , m_textColor{color}
                , m_string{text}
            {
                Text::initialize_static_members();
            }

            /// @brief Sets the text.
            void set_text(std::string_view text) { m_string = text; }

            /// @brief Sets the color of the text.
            void set_color(SDL_Color color) { m_textColor = color; }

            /// @brief Renders the text to screen.
            void render(sdl3::Renderer &renderer) override { sm_uiFont->render_text(m_x, m_y, m_textColor, m_string); }

        private:
            /// @brief String that's being displayed.
            std::string m_string{};

            /// @brief Color to use when rendering the string.
            SDL_Color m_textColor{};

            /// @brief Shared font of all UI text elements.
            static inline sdl3::SharedFont sm_uiFont{};

            /// @brief Ensures the font is loaded.
            void initialize_static_members()
            {
                if (sm_uiFont) { return; }

                sm_uiFont = sdl3::FontManager::load_resource(ui::font::PATH, ui::font::PATH, ui::font::SIZE);
            }
    };
}