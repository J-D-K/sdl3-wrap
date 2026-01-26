#pragma once
#include "objects/Object.hpp"

#include <memory>
#include <vector>

namespace objects
{
    class Container final
    {
        public:
            Container() = default;

            /// @brief Templated function that creates, stores, and returns the object created.
            /// @tparam ObjectType Type of Object to create.
            template <typename ObjectType, typename... Args>
            std::shared_ptr<ObjectType> create_new_object(Args &&...args)
            {
                static_assert(std::derived_from<ObjectType, Object> == true,
                              "Error: ObjectType is not derived from base Object!");

                // Create new object.
                auto newObject = std::make_shared<ObjectType>(std::forward<Args>(args)...);

                // Push to object vector.
                m_objects.push_back(newObject);

                return newObject;
            }

            /// @brief Allows range base for loops.
            std::vector<SharedObject>::iterator begin() noexcept { return m_objects.begin(); }

            /// @brief Allows range base for loops.
            std::vector<SharedObject>::const_iterator begin() const noexcept { return m_objects.begin(); }

            /// @brief Allows range base for loops.
            std::vector<SharedObject>::iterator end() noexcept { return m_objects.end(); }

            /// @brief Allows range base for loops.
            std::vector<SharedObject>::const_iterator end() const noexcept { return m_objects.end(); }

        private:
            /// @brief Vector of objects.
            std::vector<SharedObject> m_objects;
    };
}