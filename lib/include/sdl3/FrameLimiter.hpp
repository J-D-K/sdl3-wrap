#pragma once
#include <SDL3/SDL.h>

namespace sdl3
{
    /// @brief This class uses nanoseconds to cap framerate.
    class FrameLimiter final
    {
        public:
            /// @brief Default constructor.
            FrameLimiter() = default;

            /// @brief Constructs a new FrameLimiter.
            /// @param fps Frames per second to cap to.
            FrameLimiter(uint64_t fps) { FrameLimiter::change_fps_cap(fps); };

            /// @brief Changes the FPS cap.
            /// @param fps Frames per second desired.
            void change_fps_cap(uint64_t fps) { m_frameCap = ONE_SECOND / fps; }

            /// @brief Begins the frame cap process.
            void begin_cap() { m_frameBegin = SDL_GetTicksNS(); }

            /// @brief Ends the frame cap process.
            void end_cap()
            {
                // Calculate how long the frame took.
                const uint64_t end        = SDL_GetTicksNS();
                const uint64_t frameDelta = end - m_frameBegin;

                // If it was too short, delay.
                if (frameDelta < m_frameCap) { SDL_DelayNS(m_frameCap - frameDelta); }
            }

        private:
            /// @brief The number of nanoseconds in a second.
            static constexpr uint64_t ONE_SECOND = 1e+9;

            /// @brief Frame time for limiting. Default is 60fps.
            uint64_t m_frameCap{ONE_SECOND / 60};

            /// @brief Nanoseconds at frame begin.
            uint64_t m_frameBegin{};
    };
}