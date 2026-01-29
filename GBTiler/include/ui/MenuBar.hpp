#pragma once
#include "ui/Element.hpp"
#include "ui/Menu.hpp"

#include <memory>
#include <vector>

namespace ui
{
    class MenuBar final : public ui::Element
    {
        public:
            /// @brief MenuBar default constructor
            MenuBar() = default;

            /// @brief Update override.
            void update(const sdl3::Input &input) override;

            /// @brief Render override.
            void render(sdl3::Renderer &renderer) override;

            /// @brief Creates and adds a new menu to the MenuBar.
            std::unique_ptr<ui::Menu> &create_add_menu(std::string_view label);

        private:
            /// @brief Current X offset when piecing together the menu bar.
            int m_currentX{};

            /// @brief Vector of menus.
            std::vector<std::unique_ptr<ui::Menu>> m_menus{};
    };
}