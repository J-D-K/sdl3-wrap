#pragma once
#include <cstdint>

namespace sdl3
{
    /// @brief Basic timer class that works with ticks.
    class Timer
    {
        public:
            /// @brief Base timer constructor.
            Timer() noexcept;

            /// @brief Constructor that sets the trigger ticks.
            /// @param trigger Number of ticks to trigger the timer.
            Timer(uint64_t trigger) noexcept;

            /// @brief Resets the timer.
            void reset() noexcept;

            /// @brief Sets the trigger ticks.
            /// @param trigger Number of ticks to trigger the timer.
            void set_trigger(uint64_t trigger) noexcept;

            /// @brief Returns whether or not the timer was triggered.
            bool triggered() noexcept;

        private:
            /// @brief The ticks when the timer started.
            uint64_t m_beginTicks{};

            /// @brief Number of ticks to trigger the timer.
            uint64_t m_triggerTicks{};
    };
}