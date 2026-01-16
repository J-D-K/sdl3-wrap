#include "TestGame.hpp"
#include "sdl3.hpp"

#include <string_view>

int main(void)
{
    TestGame testGame{};

    while (testGame.is_running())
    {
        testGame.update();
        testGame.render();
    }

    return 0;
}