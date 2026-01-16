#pragma once
#include <SDL3./SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <span>
#include <string_view>

// Macro to make this less repetitive.
#define CREATE_SDL_SURFACE(x) Surface(x, SDL_DestroySurface)

namespace sdl3
{
    /// @brief Self-freeing SDL surface.
    using Surface = std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;

    /// @brief Creates and returns a new, blank, self destroying SDL_Surface.
    /// @param width Width of the surface.
    /// @param height Height of the surface.
    inline Surface create_new_surface_rgba(int width, int height)
    {
        return CREATE_SDL_SURFACE(SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888));
    }

    /// @brief Creates and returns a surface from an image using SDL_image.
    /// @param imagePath Path of the image to load.
    inline Surface create_surface_from_image(std::string_view imagePath)
    {
        return CREATE_SDL_SURFACE(IMG_Load(imagePath.data()));
    }

    inline Surface create_surface_from_memory(std::span<uint8_t> data)
    {
        // SDL IO
        SDL_IOStream *sdlIO = SDL_IOFromConstMem(data.data(), data.size());

        return CREATE_SDL_SURFACE(IMG_Load_IO(sdlIO, 1));
    }
}

#undef CREATE_SDL_SURFACE