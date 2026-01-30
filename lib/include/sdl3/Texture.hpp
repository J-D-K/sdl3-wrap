#pragma once

#include "Renderer.hpp"
#include "Surface.hpp"

#include <SDL3/SDL.h>
#include <filesystem>

namespace sdl3
{
    /// @brief This makes some stuff easier even if I don't like it.
    class Renderer;

    /// @brief Forward to allow the following.
    class Texture;

    /// @brief This makes things easier to type.
    using SharedTexture = std::shared_ptr<Texture>;

    /// @brief Texture wrapper class.
    class Texture final
    {
        public:
            /// @brief This is a null texture for targeting the framebuffer.
            static inline sdl3::SharedTexture NullTexture = std::make_shared<sdl3::Texture>();

            /// @brief Default constructor. Should not be used. Only for setting up the Null texture.
            Texture() = default;

            /// @brief Creates and loads a texture from the path passed.
            /// @param renderer Pointer to the renderer used by the texture.
            /// @param texturePath Path to the texture to load.
            Texture(std::string_view texturePath);

            /// @brief Creates a texture from the surface passed.
            /// @param renderer Pointer to the renderer used by the texture.
            /// @param surface Surface to create the texture from.
            Texture(sdl3::Surface &surface);

            /// @brief Creates a blank texture using the flags passed.
            /// @param renderer Pointer to the renderer used by the texture.
            /// @param width Width of the texture.
            /// @param height Height of the texture.
            /// @param accessFlags Access flags.
            Texture(SDL_Renderer *renderer, int width, int height, SDL_TextureAccess accessFlags);

            /// @brief Frees the texture once it's finished.
            ~Texture();

            /// @brief Returns the width of the sprite.
            int get_width() const noexcept;

            /// @brief Returns the height of the sprite.
            int get_height() const noexcept;

            /// @brief Set's the alpha mod of the texture.
            /// @param alpha Alpha to render with.
            /// @return True on success. False on failure.
            bool set_alpha_mod(uint8_t alpha);

            /// @brief Sets the render color mod for the texture.
            /// @param colorMod Color to mod the render color for.
            /// @return True on success. False on failure.
            bool set_color_mod(SDL_Color colorMod);

            /// @brief Sets the scale mode for the texture.
            /// @param scaleMode Scale mode to set to.
            /// @return True on success. False on failure.
            bool set_scale_mode(SDL_ScaleMode scaleMode);

            /// @brief Renders the texture to the target passed at the coordinates passed.
            /// @param target Target to render to.
            /// @param x X coordinate.
            /// @param y Y coordinate.
            /// @return True on success. False on failure.
            bool render(int x, int y);

            /// @brief Renders the texture to the target passed stretched to width and height.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param width Width to render at.
            /// @param height Height to render at.
            /// @return True on success. False on failure.
            bool render_stretched(int x, int y, int width, int height);

            /// @brief Renders a part of the texture to the coordinates passed.
            /// @param target Target to render to.
            /// @param x X coordinate to render to.
            /// @param y Y coordinate to render to.
            /// @param sourceX Source X coordinate of the part to render.
            /// @param sourceY Source Y coordinate of the part to render.
            /// @param sourceWidth Width of the part to render.
            /// @param sourceHeight Height of the part to render.
            /// @return True on success. False on failure.
            bool render_part(int x, int y, int sourceX, int sourceY, int sourceWidth, int sourceHeight);

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
            bool render_part_stretched(int x,
                                       int y,
                                       int width,
                                       int height,
                                       int sourceX,
                                       int sourceY,
                                       int sourceWidth,
                                       int sourceHeight);

            /// @brief Sets the current renderer for creating and rendering textures.
            /// @param renderer Renderer to set.
            static void set_renderer(const sdl3::Renderer &renderer);

            /// @brief Allows for the renderer to set targets easier.
            friend class Renderer;

        private:
            /// @brief Pointer to the underlying SDL_Texture.
            SDL_Texture *m_texture{};

            /// @brief Width of the texture.
            float m_width{};

            /// @brief Height of the texture.
            float m_height{};

            /// @brief Flag storing whether or not the texture is valid.
            bool m_isValid{};

            /// @brief Shared renderer pointer.
            static inline SDL_Renderer *sm_renderer{};
    };
}