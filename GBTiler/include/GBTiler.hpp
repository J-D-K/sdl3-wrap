#pragma once
#include "sdl3.hpp"
#include "ui/Element.hpp"
#include "ui/MenuBar.hpp"
#include "ui/Text.hpp"

#include <memory>
#include <span>
#include <vector>

class GBTiler final
{
    public:
        /// @brief Constructor. Creates the main tiling application.
        /// @param argv Commandline arguments.
        GBTiler(std::span<const char *> argv);

        /// @brief Executes the GBTiler main loop.
        int run();

        /// @brief Templated function to make adding elements to the application easier.
        /// @tparam ElementType Type of element to create.
        /// @tparam ...Args Arguments to forward to the element constructor.
        /// @return Reference to unique_ptr in m_elements vector.
        template <typename ElementType, typename... Args>
        inline std::shared_ptr<ElementType> new_ui_element(Args &&...args)
        {
            // Make sure it's derived from Element.
            static_assert(std::derived_from<ElementType, ui::Element> == true, "Error: Class is not derived from ui::Element!");

            // Create and push.
            m_elements.push_back(std::make_shared<ElementType>(std::forward<Args>(args)...));

            // Return the back.
            return std::static_pointer_cast<ElementType>(m_elements.back());
        }

    private:
        /// @brief Whether or not the program should keep running.
        bool m_running{};

        /// @brief SDL3 instance.
        sdl3::SDL3 m_sdl3{};

        /// @brief SDL3 window.
        sdl3::Window m_window{};

        /// @brief SDL3 renderer.
        sdl3::Renderer m_renderer{};

        /// @brief Input instance.
        sdl3::Input m_input{};

        /// @brief Frame limiter so the tiler runs at 60FPS.
        sdl3::FrameLimiter m_frameLimiter{};

        /// @brief Menu bar.
        std::shared_ptr<ui::MenuBar> m_menuBar{};

        /// @brief These are just debugging strings.
        std::shared_ptr<ui::Text> m_mouseCoords{};

        /// @brief Vector of elements.
        std::vector<std::shared_ptr<ui::Element>> m_elements{};

        /// @brief Updates elements.
        void update();

        /// @brief Renders elements.
        void render();

        /// @brief Initializes the menu bar and pushes it to the element vector.
        void initialize_menu_bar();

        /// @brief Creates the file menu and adds it to the menu bar.
        void initialize_file_menu();

        /// @brief Initializes the layer changing menu.
        void initialize_layer_menu();
};