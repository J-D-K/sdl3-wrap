#include "util/filename.hpp"

#include <algorithm>
#include <array>
#include <windows.h>

namespace
{
    constexpr size_t STRUCT_SIZE = sizeof(OPENFILENAMEA);
}

std::string util::get_open_filename(std::string_view path, std::string_view filter)
{

    // Array to pass and store name.
    std::array<char, MAX_PATH> pathBuffer{};
    std::copy(path.begin(), path.end(), pathBuffer.begin());

    // Windows struct. To do: Support for Linux too.
    OPENFILENAMEA openFileName{};
    openFileName.lStructSize = STRUCT_SIZE;
    openFileName.lpstrFilter = filter.data();
    openFileName.lpstrFile   = pathBuffer.data();
    openFileName.nMaxFile    = MAX_PATH;

    const WINBOOL success = GetOpenFileNameA(&openFileName);
    if (success == FALSE) { return {}; }

    return std::string{pathBuffer.data()};
}

std::string util::get_save_filename(std::string_view path, std::string_view filter)
{
    std::array<char, MAX_PATH> pathBuffer{};
    std::copy(path.begin(), path.end(), pathBuffer.begin());

    OPENFILENAMEA saveFileName{};
    saveFileName.lStructSize = STRUCT_SIZE;
    saveFileName.lpstrFilter = filter.data();
    saveFileName.lpstrFile   = pathBuffer.data();
    saveFileName.nMaxFile    = MAX_PATH;

    const WINBOOL success = GetSaveFileNameA(&saveFileName);
    if (success == FALSE) { return {}; }

    return std::string{pathBuffer.data()};
}