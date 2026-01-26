#pragma once
#include "sdl3.hpp"

namespace ui
{
    class Element
    {
        public:
            /// @brief Default constructor.
            Element() = default;

            /// @brief Constructor that allows setting X and Y.
            Element(int x, int y)
                : m_x{x}
                , m_y{y} {};

            /// @brief Constructor that allows setting X, Y, Width, and Height.
            Element(int x, int y, int width, int height)
                : m_x{x}
                , m_y{y}
                , m_width{width}
                , m_height{height} {};

            /// @brief Virtual update function.
            /// @param input Reference to sdl3 input instance.
            virtual void update(const sdl3::Input &input) {};

            /// @brief Virtual render function.
            /// @param renderer Reference to SDL3 renderer instance.
            virtual void render(sdl3::Renderer &renderer) {}

            /// @brief Sets the X and Y coordinates of the Element.
            /// @param x X to set.
            /// @param y Y to set.
            void set_x_y(int x, int y)
            {
                m_x = x;
                m_y = y;
            }

            /// @brief Returns whether or not the mouse is within the X and Y coordinates of the element.
            inline bool mouse_is_within(const sdl3::Input &input)
            {
                // Grab mouse coordinates.
                const int mouseX = input.get_mouse_x();
                const int mouseY = input.get_mouse_y();

                // Check if the mouse is outside our area and return the inverse.
                const bool outsideX = mouseX < m_x || mouseX > m_x + m_width;
                const bool outsideY = mouseY < m_y || mouseY > m_y + m_height;

                return !outsideX && !outsideY;
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
    };
}