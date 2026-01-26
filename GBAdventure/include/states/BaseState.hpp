#pragma once
#include "objects/Container.hpp"
#include "sdl3.hpp"

#include <memory>

namespace states
{
    class BaseState
    {
        public:
            /// @brief Default constructor.
            BaseState() = default;

            /// @brief Virtual update function.
            /// @param input Reference to sdl3 input wrapper.
            virtual void update(const sdl3::Input &input) {};

            /// @brief Virtual render function.
            /// @param renderer Reference to sdl3 renderer instance.
            virtual void render(sdl3::Renderer &renderer) {}

        protected:
            /// @brief Object container.
            objects::Container m_objects;
    };
}