#pragma once
#include "ui/Element.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ui
{
    /// @brief Forward for less headaches.
    class MenuBar;

    /// @brief Menu class.
    class Menu final : public ui::Element
    {
        public:
            /// @brief Menu constructor.
            /// @param x X coordinate of the menu.
            /// @param y Y coordinate of the menu.
            /// @param menuName Name/Label displayed.
            Menu(std::string_view menuName);

            /// @brief Inline creation function.
            static inline std::unique_ptr<Menu> create(std::string_view label) { return std::make_unique<Menu>(label); }

            /// @brief Adds a suboption to the menu.
            /// @param option Text/label displayed.
            /// @param onClick Function executed on click.
            void add_sub_option(std::string_view option, std::function<void()> onClick);

            /// @brief Update override.
            void update(const sdl3::Input &input) override;

            /// @brief Render override.
            void render(sdl3::Renderer &renderer) override;

            /// @brief Less headaches.
            friend class MenuBar;

        private:
            /// @brief Enum for states the menu can be in.
            enum class State : uint8_t
            {
                Idle,
                Hovered,
                Clicked
            };

            /// @brief Menu label.
            const std::string m_label{};

            /// @brief X coordinate for rendering the label.
            int m_labelX{};

            /// @brief Y coordinate for rendering the label.
            int m_labelY{};

            /// @brief Width of the label text.
            int m_labelWidth{};

            /// @brief State the menu is currently in.
            Menu::State m_state{};

            /// @brief Vector of sub options and their on click function.
            std::vector<std::pair<std::string, std::function<void()>>> m_subOptions{};

            /// @brief Shared pointer to the UI font.
            static inline sdl3::SharedFont sm_uiFont{};

            /// @brief Inits the UI font and sets if it hasn't been already.
            void initialize_static_members();

            /// @brief Renders the main label menu as idle.
            void render_idle(sdl3::Renderer &renderer);

            /// @brief Renders the main label menu as hovered.
            void render_hover(sdl3::Renderer &renderer);
    };
}