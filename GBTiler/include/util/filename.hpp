#pragma once
#include <string>

namespace util
{
    /// @brief Opens and attempts to get an open filename.
    /// @param path Default path.
    /// @param filter Filter for file types.
    /// @return Path on success, empty on failure.
    std::string get_open_filename(std::string_view path, std::string_view filter);

    /// @brief Same as get_open_filename, only saving.
    std::string get_save_filename(std::string_view path, std::string_view filter);
}
