#pragma once

#include "Texture.hpp"

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace sdl3
{
    /// @brief Templated resource manager.
    /// @tparam ResourceType
    template <typename ResourceType>
    class ResourceManager final
    {
        public:
            /// @brief No copying or moving.
            ResourceManager(const ResourceManager &)            = delete;
            ResourceManager(ResourceManager &&)                 = delete;
            ResourceManager &operator=(const ResourceManager &) = delete;
            ResourceManager &operator=(ResourceManager &&)      = delete;

            template <typename... Args>
            static std::shared_ptr<ResourceType> load_resource(std::string_view resourcePath, Args &&...args)
            {
                // Grab instance and map.
                ResourceManager &manager = ResourceManager::get_instance();
                auto &resourceMap        = manager.m_resourceMap;

                // Purge unused/expired resources.
                // manager.purge_expired();

                // Search to see if the resource has been loaded previously.
                auto findResource = resourceMap.find(resourcePath);

                // If the resource was found and it wasn't expired, return it.
                if (findResource != resourceMap.end() && !findResource->second.expired())
                {
                    return findResource->second.lock();
                }
                else
                {
                    // Create and load the resource.
                    auto resource = std::make_shared<ResourceType>(resourcePath, std::forward<Args>(args)...);

                    // Map.
                    resourceMap.try_emplace(std::string{resourcePath}, resource);

                    return resource;
                }

                return nullptr;
            }

        private:
            // clang-format off
            /// @brief Struct for string view hashing.
            struct StringViewHash
            {
                using is_transparent = void;
                size_t operator()(std::string_view view) const noexcept { return std::hash<std::string_view>{}(view); }
            };

            struct StringViewEquals
            {
                using is_transparent = void;
                bool operator()(std::string_view viewA, std::string_view viewB) const noexcept { return viewA == viewB; }
            };
            // clang-format on.

            /// @brief Map with weak pointers to currently loaded resources.
            std::unordered_map<std::string, std::weak_ptr<ResourceType>, StringViewHash, StringViewEquals> m_resourceMap{};

            /// @brief Default constructor.
            ResourceManager() = default;

            /// @brief Returns the only instance to the class.
            /// @return Reference to instance.
            static ResourceManager &get_instance()
            {
                static ResourceManager manager{};

                return manager;
            }

            /// @brief Purges the expired resources from the map.
            void purge_expired()
            {
                // Loop through map.
                for(auto iter = m_resourceMap.begin(); iter != m_resourceMap.end();)
                {
                    // Reference to weak_ptr.
                    auto &weakPointer = iter->second;

                    // If it's expired, purge from map.
                    if(weakPointer.expired())
                    {
                        iter = m_resourceMap.erase(iter);
                        continue;
                    }
                    ++iter;
                }
            }
    };

    /// @brief Definition for the TextureManager.
    using TextureManager = sdl3::ResourceManager<sdl3::Texture>;
}