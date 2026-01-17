#pragma once

#include <optional>

namespace sdl3
{
    template <typename Type>
    using OptionalReference = std::optional<std::reference_wrapper<Type>>;

}