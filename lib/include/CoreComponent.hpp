#pragma once

namespace sdl3
{
    /// @brief Core component base class.
    class CoreComponent
    {
        public:
            /// @brief Default constructor.
            CoreComponent() = default;

            /// @brief Returns whether or not the component initialized successfully.
            bool is_initialize() const noexcept { return m_initialized; }

        protected:
            /// @brief Stores whether or not the component was initialized successfully.
            bool m_initialized{};
    };
}