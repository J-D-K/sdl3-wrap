#pragma once

namespace sdl3
{
    class CoreComponent
    {
        public:
            /// @brief Default constructor.
            CoreComponent() = default;

            /// @brief Returns whether or not the component was initialized successfully.
            bool is_initialized() const noexcept { return m_isInitialized; }

        protected:
            /// @brief Store whether or not the component was initialized successfully.
            bool m_isInitialized{};
    };
}