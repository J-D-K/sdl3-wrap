#pragma once

#include "Object.hpp"
#include "SDL3.hpp"

#include <memory>
#include <span>
#include <vector>

class Game final
{
    public:
        /// @brief Constructor. Inits SDL and creates window.
        Game();

        /// @brief Runs the game.
        int run() noexcept;

        /// @brief Returns the game objects as a span.
        std::span<const UniqueObject> get_game_objects() const noexcept;

        /// @brief Adds the passed value to the score of the player.
        /// @param addScore Score to add.
        void add_to_score(int64_t addScore) noexcept;

        /// @brief Templated function to allow easier insertion of new object instances into the main game vector.
        /// @tparam ObjectType Type of object.
        /// @tparam ...Args Templated argument types to forward.
        /// @param ...args Arguments to forward.
        template <typename ObjectType, typename... Args>
        void create_add_object(Args &&...args)
        {
            // Asset the template type is derived from Object.
            static_assert(std::derived_from<ObjectType, Object>, "Object type created is not derived from base Object!");

            // Create and push it.
            m_objects.push_back(std::make_unique<ObjectType>(std::forward<Args>(args)...));
        }

    private:
        /// @brief Game score.
        int64_t m_score{};

        /// @brief SDL3 Container instance.
        sdl3::SDL3 m_sdl3{};

        /// @brief Window instance.
        sdl3::Window m_window{};

        /// @brief Renderer instance.
        sdl3::Renderer m_renderer{};

        /// @brief Keyboard instance.
        sdl3::Keyboard m_keyboard{};

        /// @brief Mouse instance.
        sdl3::Mouse m_mouse{};

        /// @brief Test font.
        sdl3::SharedFont m_font{};

        /// @brief Vector of game objects.
        std::vector<std::unique_ptr<Object>> m_objects{};

        /// @brief Runs the update routine.
        /// @param input Reference to input passed from run.
        void update() noexcept;

        /// @brief Runs the render routine.
        void render() noexcept;

        /// @brief Purges all of the offscreen objects.
        void purge_uneeded_objects();

        /// @brief Sorts the object vector by depth for rendering.
        void sort_objects_by_depth();
};