#include "SDL3.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void)
{
    sdl3::SDL3 sdl3{};
    sdl3::GamepadManager padManager{};

    while (true)
    {
        // Keep pumpin.
        sdl3.pump_events();

        // Update the manager.
        padManager.update();

        // Store these.
        const bool connect    = padManager.new_pad_connected();
        const bool disconnect = padManager.pad_disconnected();
        const bool change     = connect || disconnect;

        // Continue the loop if no changes occurred.
        if (!change) { continue; }

        std::cout << "Change Detected!" << std::endl;
        for (const auto &pad : padManager)
        {
            std::cout << "Pad ID: " << pad.get_id() << ", Name: " << pad.get_name() << std::endl;
        }
    }
}