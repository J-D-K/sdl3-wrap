#pragma once
#include "ui/Element.hpp"

#include <functional>
#include <string>

namespace ui
{
    class MenuOption final : public ui::Element
    {
        public:
            /// @brief Constructs a new menu option.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param label Label of the sub option.
            /// @param onClick Function executed when the suboption is clicked.
            /// @note This shouldn't be used directly.
            MenuOption(int x, int y, std::string_view label, std::function<void()> onClick);

            /// @brief Update override.
            void update(const sdl3::Input &input) override;

            /// @brief Render override.
            /// @param renderer
            void render(sdl3::Renderer &renderer) override;

        private:
            /// @brief Enum for states the option can be in.
            enum class State : uint8_t
            {
                Idle,
                Hover
            };

            /// @brief Owning string to store the label.
            std::string m_label{};

            /// @brief Stores the onClick function.
            std::function<void()> m_onClick{};

            /// @brief Y coordinate to render the label to.
            int m_labelY{};

            /// @brief Width of the label of the option.
            size_t m_labelWidth{};

            /// @brief State the option is in.
            MenuOption::State m_state{};

            /// @brief Update routine for when the option is idle.
            void update_idle(const sdl3::Input &input) noexcept;

            /// @brief Update routine for when the option is being hovered.
            void update_hover(const sdl3::Input &input) noexcept;

            /// @brief Renders the option in its idle state.
            void render_idle(sdl3::Renderer &renderer);

            /// @brief Renders the option in its hover state.
            void render_hover(sdl3::Renderer &renderer);
    };
}
