#pragma once
#include "objects/Object.hpp"

#include <array>
#include <string>
#include <vector>

namespace objects
{
    class Menu final : public objects::Object
    {
        public:
            /// @brief Default constructor.
            Menu();

            /// @brief Constructor.
            /// @param x X render coordinate.
            /// @param y Y render coordinate.
            /// @param optionList List of options for the menu.
            Menu(int x, int y, std::span<const std::string_view> optionList);

            /// @brief Returns the currently selected option.
            int get_selected() const noexcept;

            /// @brief Sets the currently selected option.
            void set_selected(int selected) noexcept;

            /// @brief Sets the X and Y of the menu.
            /// @param x X to set.
            /// @param y Y to set.
            void set_x_y(int x, int y) noexcept;

            /// @brief Update routine.
            /// @param input Reference to input instance.
            void update(const sdl3::Input &input);

            /// @brief Render routine.
            /// @param renderer Reference to renderer instance.
            void render(sdl3::Renderer &renderer);

        private:
            /// @brief Selected option.
            int m_selected{};

            /// @brief Vector of options with memory owned by the class just in case.
            std::vector<std::string> m_options;

            /// @brief Shared pointer texture.
            static inline sdl3::SharedTexture sm_pointer{};

            /// @brief Shared pointer to the font.
            static inline sdl3::SharedFont sm_font{};

            /// @brief Loads the shared pointer texture.
            void initialize_static_members();
    };
}