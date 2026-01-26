#pragma once
#include "objects/Menu.hpp"
#include "sdl3.hpp"
#include "states/BaseState.hpp"

namespace states
{
    class Titlescreen final : public states::BaseState
    {
        public:
            /// @brief Titlescreen constructor.
            Titlescreen();

            /// @brief Update routine.
            /// @param input Reference to input instance.
            void update(const sdl3::Input &input) override;

            /// @brief Render routine.
            /// @param renderer Reference to renderer instance.
            void render(sdl3::Renderer &renderer) override;

        private:
            /// @brief X coordinate of the title.
            int m_titleX{};

            /// @brief Shared pointer to menu for later access.
            std::shared_ptr<objects::Menu> m_menu{};

            /// @brief Font to render text.
            sdl3::SharedFont m_font{};
    };
}