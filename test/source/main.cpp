#include "Game.hpp"
#include "sdl3.hpp"

#include <cstdlib>
#include <ctime>
#include <string_view>

int main(void)
{
    // Start by seeding the random generator.
    std::srand(std::time(nullptr));

    // Game instance.
    Game game{};

    // Run the game.
    return game.run();
}