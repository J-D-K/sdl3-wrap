#pragma once
#include "ui/Element.hpp"
#include "ui/MenuOption.hpp"

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
            /// @param label Text/label displayed.
            /// @param onClick Function executed on click.
            void add_sub_option(std::string_view label, std::function<void()> onClick);

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

            /// @brief The current Y coordinate for creating sub-options.
            int m_subY{};

            /// @brief Width of the menu when it's opened.
            int m_openWidth{};

            /// @brief The height of the menu when it's opened.
            int m_openHeight{};

            /// @brief State the menu is currently in.
            Menu::State m_state{};

            /// @brief Vector of sub options and their on click function.
            std::vector<ui::MenuOption> m_subOptions{};

            /// @brief Handles updating the state for idle.
            void update_idle(const sdl3::Input &input) noexcept;

            /// @brief Handles updating the state for hovering.
            void update_hover(const sdl3::Input &input) noexcept;

            /// @brief Handles updating the state when the menu is clicked or open.
            void update_clicked(const sdl3::Input &input) noexcept;

            /// @brief Renders the main label menu as idle.
            void render_idle(sdl3::Renderer &renderer);

            /// @brief Renders the main label menu as hovered.
            void render_hover(sdl3::Renderer &renderer);

            /// @brief Renders the main label as hovered and the suboptions.
            void render_clicked(sdl3::Renderer &renderer);

            /// @brief Checks and updates the sub-option width.
            void update_sub_options() noexcept;

            /// @brief Renders the sub options.
            void render_sub_options(sdl3::Renderer &renderer) noexcept;
    };
}