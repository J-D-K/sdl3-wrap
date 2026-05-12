#include "SDL3.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void)
{
    sdl3::SDL3 sdl3{};

    sdl3::GamepadScanner scanner{};

    if (!scanner.is_initialized())
    {
        std::cout << "Error initializing GamepadScanner!" << std::endl;
        return -1;
    }

    std::cout << "Gamepad count: " << scanner.count() << std::endl;

    for (const auto &joystick : scanner) { std::cout << "Joystick ID: " << joystick << std::endl; }
}