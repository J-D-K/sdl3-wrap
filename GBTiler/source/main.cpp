#include "GBTiler.hpp"

#include <span>

int main(int argc, const char *argv[])
{
    GBTiler gbTiler{std::span<const char *>{argv, static_cast<size_t>(argc)}};
    return gbTiler.run();
}