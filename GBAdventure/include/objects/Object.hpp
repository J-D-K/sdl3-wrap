#pragma once
#include "sdl3.hpp"

#include <memory>

namespace objects
{
    /// @brief I prefer this like this.
    class Object;

    /// @brief Allows easier typing and clarity.
    using SharedObject = std::shared_ptr<objects::Object>;

    /// @brief Base Object class.
    class Object
    {
        public:
            /// @brief Default constructor.
            Object() = default;

            /// @brief Virtual update function.
            /// @param game Reference to Game instance.
            /// @param input Reference to input instance.
            virtual void update(const sdl3::Input &input) {};

            /// @brief Virtual render function.
            /// @param renderer Reference to renderer instance.
            virtual void render(sdl3::Renderer &renderer) {};

        protected:
            /// @brief X coordinate.
            int m_x{};

            /// @brief Y coordinate.
            int m_y{};

            /// @brief Width of the object.
            int m_width{};

            /// @brief Height of the object.
            int m_height{};
    };
}