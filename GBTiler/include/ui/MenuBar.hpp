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

            /// @brief Adds a menu to the menu bar.
            /// @param menu Unique ptr to menu added.
            void add_menu(std::unique_ptr<ui::Menu> &menu);

        private:
            /// @brief Current X offset when piecing together the menu bar.
            int m_currentX{};

            /// @brief Vector of menus.
            std::vector<std::unique_ptr<ui::Menu>> m_menus{};
    };
}