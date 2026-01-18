#pragma once

#include "Object.hpp"
#include "sdl3.hpp"

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
            static_assert(std::derived_from<ObjectType, Object> == true,
                          "Object type created is not derived from base Object!");

            // Create and push it.
            m_objects.push_back(std::make_unique<ObjectType>(std::forward<Args>(args)...));
        }

    private:
        /// @brief Game score.
        int64_t m_score{};

        /// @brief Test font.
        sdl3::SharedFont m_font{};

        /// @brief Vector of game objects.
        std::vector<std::unique_ptr<Object>> m_objects{};

        /// @brief Runs the update routine.
        /// @param input Reference to input passed from run.
        void update(const sdl3::Input &input) noexcept;

        /// @brief Runs the render routine.
        void render() noexcept;

        /// @brief Purges all of the offscreen objects.
        void purge_offscreen_objects();

        /// @brief Sorts the object vector by depth for rendering.
        void sort_objects_by_depth();
};