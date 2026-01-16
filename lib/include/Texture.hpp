#pragma once

#include "Surface.hpp"

#include <SDL3/SDL.h>
#include <filesystem>

namespace sdl3
{
    /// @brief Forward to allow the following.
    class Texture;

    /// @brief This makes things easier to type.
    using SharedTexture = std::shared_ptr<Texture>;

    class Texture final
    {
        public:
            /// @brief This is a null texture for targeting the framebuffer.
            static inline sdl3::SharedTexture NullTexture = std::make_shared<sdl3::Texture>();

            /// @brief Default constructor. Should not be used. Only for setting up the Null texture.
            Texture() = default;

            /// @brief Creates and loads a texture from the path passed.
            /// @param texturePath Path to the texture to load.
            Texture(std::string_view texturePath);

            /// @brief Creates a texture from the surface passed.
            /// @param surface Surface to create the texture from.
            Texture(sdl3::Surface &surface);

            /// @brief Creates a blank texture using the flags passed.
            /// @param width Width of the texture.
            /// @param height Height of the texture.
            /// @param accessFlags Access flags.
            Texture(int width, int height, SDL_TextureAccess accessFlags);

            /// @brief Frees the texture once it's finished.
            ~Texture();

            /// @brief Renders the texture to the target passed at the coordinates passed.
            /// @param target Target to render to.
            /// @param x X coordinate.
            /// @param y Y coordinate.
            /// @return True on success. False on failure.
            bool render_to(SharedTexture &target, int x, int y);

            /// @brief Renders the texture to the target passed stretched to width and height.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param width Width to render at.
            /// @param height Height to render at.
            /// @return True on success. False on failure.
            bool render_to_stretched(SharedTexture &target, int x, int y, int width, int height);

            /// @brief Renders a part of the texture to the coordinates passed.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param sourceX Source X coordinate of the part to render.
            /// @param sourceY Source Y coordinate of the part to render.
            /// @param sourceWidth Width of the part to render.
            /// @param sourceHeight Height of the part to render.
            /// @return True on success. False on failure.
            bool render_part_to(SharedTexture &target,
                                int x,
                                int y,
                                int sourceX,
                                int sourceY,
                                int sourceWidth,
                                int sourceHeight);

            /// @brief Renders a part of the texture stretched to the target passed.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param width Width to render at.
            /// @param height Height to render at.
            /// @param sourceX Source X coordinate of the part to render.
            /// @param sourceY Source Y coordinate of the part to render.
            /// @param sourceWidth Width of the source to render to.
            /// @param sourceHeight Height of the source to render to.
            /// @return True on success. False on failure.
            bool render_part_to_stretched(SharedTexture &target,
                                          int x,
                                          int y,
                                          int width,
                                          int height,
                                          int sourceX,
                                          int sourceY,
                                          int sourceWidth,
                                          int sourceHeight);

        private:
            /// @brief Pointer to the underlying SDL_Texture.
            SDL_Texture *m_texture{};

            /// @brief Width of the texture.
            float m_width{};

            /// @brief Height of the texture.
            float m_height{};

            /// @brief Flag storing whether or not the texture is valid.
            bool m_isValid{};

            /// @brief Shared pointer to the renderer to avoid repeated calls to SDL3::get_renderer().
            static inline SDL_Renderer *sm_renderer{};

            /// @brief Initializes the pointer to the renderer shared by all texture instances.
            void initialize_static_members();
    };
}