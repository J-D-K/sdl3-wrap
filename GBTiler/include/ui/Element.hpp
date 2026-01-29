#pragma once
#include "sdl3.hpp"
#include "ui/font.hpp"
#include "util/is_within.hpp"

namespace ui
{
    /// @brief Base UI Element.
    class Element
    {
        public:
            /// @brief Default constructor.
            Element() { Element::initialize_static_members(); }

            /// @brief Constructor that allows setting X and Y.
            Element(int x, int y)
                : m_x{x}
                , m_y{y}
            {
                Element::initialize_static_members();
            }

            /// @brief Constructor that allows setting X, Y, Width, and Height.
            Element(int x, int y, int width, int height)
                : m_x{x}
                , m_y{y}
                , m_width{width}
                , m_height{height}
            {
                Element::initialize_static_members();
            }

            /// @brief Virtual update function.
            /// @param input Reference to sdl3 input instance.
            virtual void update(const sdl3::Input &input) {};

            /// @brief Virtual render function.
            /// @param renderer Reference to SDL3 renderer instance.
            virtual void render(sdl3::Renderer &renderer) {}

            /// @brief Returns the X.
            int get_x() const noexcept { return m_x; }

            /// @brief Returns the Y.
            int get_y() const noexcept { return m_y; }

            /// @brief Returns the width.
            int get_width() const noexcept { return m_width; }

            /// @brief Returns the height.
            int get_height() const noexcept { return m_height; }

            /// @brief Sets the X.
            virtual void set_x(int x) noexcept { m_x = x; }

            /// @brief Sets the Y.
            virtual void set_y(int y) noexcept { m_y = y; }

            /// @brief Sets the width.
            virtual void set_width(int width) noexcept { m_width = width; }

            /// @brief Sets the height.
            virtual void set_height(int height) noexcept { m_height = height; }

            /// @brief Returns whether or not the mouse is within the X and Y coordinates of the element.
            inline bool mouse_is_within(const sdl3::Input &input)
            {
                // Grab mouse coordinates.
                const int mouseX = input.get_mouse_x();
                const int mouseY = input.get_mouse_y();

                return util::is_within(mouseX, mouseY, m_x, m_y, m_width, m_height);
            }

        protected:
            /// @brief X coordinate to render to.
            int m_x{};

            /// @brief Y coordinate to render to.
            int m_y{};

            /// @brief Width of the element.
            int m_width{};

            /// @brief Height of the element.
            int m_height{};

            /// @brief Static pointer to the UI font all elements share.
            static inline sdl3::SharedFont sm_uiFont{};

            /// @brief Initializes the static members.
            void initialize_static_members()
            {
                if (sm_uiFont) { return; }

                sm_uiFont = sdl3::FontManager::load_resource(ui::font::PATH, ui::font::PATH, ui::font::SIZE);
            }
    };
}