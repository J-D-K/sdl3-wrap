#include "WindowTest.hpp"

#include <cstdlib>
#include <ctime>

int main(void)
{
    std::srand(std::time(nullptr));

    WindowTest windowTest{};

    return windowTest.run();
}