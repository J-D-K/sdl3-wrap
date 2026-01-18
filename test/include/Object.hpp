#pragma once
#include "SDL3.hpp"

#include <memory>

/// @brief This is to prevent header clashes.
class Game;

/// @brief This allows me to get some stuff out of the way I'd prefer at the top.
class Object;

/// @brief Makes things easier to type.
using UniqueObject = std::unique_ptr<Object>;

class Object
{
    public:
        enum class Type
        {
            Unspecified,
            Bullet,
            Enemy,
            Player,
            Star
        };

        /// @brief Constructor. Stores object type.
        Object(Type type)
            : m_type{type} {};

        /// @brief Virtual destructor.
        virtual ~Object() {};

        /// @brief Virtual update.
        virtual void update(Game &game, const sdl3::Input &input) {};

        /// @brief Virtual render.
        virtual void render() {};

        /// @brief Return the X coordinate.
        int get_x() const noexcept { return m_x; }

        /// @brief Return the Y coordinate.
        int get_y() const noexcept { return m_y; }

        /// @brief Return the width.
        int get_width() const noexcept { return m_width; }

        /// @brief Return the height.
        int get_height() const noexcept { return m_height; }

        /// @brief Return the depth.
        int get_depth() const noexcept { return m_depth; }

        /// @brief Returns the object type.
        Type get_type() const noexcept { return m_type; }

        /// @brief Marks the object as purgable.
        void mark_for_purge() noexcept { m_isPurgable = true; }

        /// @brief Returns whether or not the object has marked itself as purgable.
        bool is_purgable() const noexcept { return m_isPurgable; }

        /// @brief Returns if there's a collision with the object passed.
        /// @param object Object to check.
        bool collision(const UniqueObject &object) const noexcept
        {
            // We're going to actually check if there's no collision. It's easier.
            const bool noXCollision = object->m_x + object->m_width < m_x || object->m_x > m_x + m_width;
            const bool noYCollision = object->m_y + object->m_height < m_y || object->m_y > m_y + m_height;

            // Return if both of the above are false.
            return !noXCollision && !noYCollision;
        }

    protected:
        /// @brief X coordinate.
        int m_x{};

        /// @brief Y coordinate.
        int m_y{};

        /// @brief Object width.
        int m_width{};

        /// @brief Object height.
        int m_height{};

        /// @brief Depth of the object.
        int m_depth{};

        /// @brief Type of Object.
        Type m_type{};

        /// @brief Allows the object to mark itself as purgable for the main Game class.
        bool m_isPurgable{};

        /// @brief Sprite to render.
        sdl3::SharedTexture m_sprite{};
};