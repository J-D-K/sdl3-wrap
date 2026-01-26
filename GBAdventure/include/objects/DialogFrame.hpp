#pragma once
#include "objects/Object.hpp"

namespace objects
{
    /// @brief Dialog frame class.
    class DialogFrame final : public objects::Object
    {
        public:
            /// @brief Default constructor.
            DialogFrame();

            /// @brief Constructor. Sets the area of the dialog frame.
            DialogFrame(int x, int y, int width, int height);

            /// @brief Sets the area of the dialog frame.
            void set_area(int x, int y, int width, int height) noexcept;

            // This uses the default, blank, stubbed base update routine.

            /// @brief Render routine.
            void render(sdl3::Renderer &renderer) override;

        private:
            /// @brief All instances share this.
            static inline sdl3::SharedTexture sm_dialogTexture{};

            /// @brief Loads the dialog frame texture.
            void initialize_static_members();
    };
}