#pragma once
#include "Gamepad.hpp"
#include "OptionalReference.hpp"

#include <SDL3/SDL.h>
#include <memory>
#include <span>
#include <vector>

namespace sdl3
{
    /// @brief Gamepad manager class.
    class GamepadManager final
    {
        public:
            // These make things easier to read and type.
            using PadVector    = std::vector<sdl3::Gamepad>;
            using PadIter      = PadVector::iterator;
            using ConstPadIter = PadVector::const_iterator;

            // This is for wrapping an SDL3 api.
            using JoystickIDArray = std::unique_ptr<SDL_JoystickID, decltype(&SDL_free)>;

            // No copying or moving.
            GamepadManager(const GamepadManager &)            = delete;
            GamepadManager(GamepadManager &&)                 = delete;
            GamepadManager &operator=(const GamepadManager &) = delete;
            GamepadManager &operator=(GamepadManager &&)      = delete;

            /// @brief Default constructor.
            GamepadManager() = default;

            /// @brief Returns whether or not a new gamepad was detected.
            bool new_pad_connected() const noexcept;

            /// @brief Returns whether or not a game pad was disconnected.
            bool pad_disconnected() const noexcept;

            /// @brief Retuns the number of pads currently initialized and ready to go in the manager.
            size_t pad_count() const noexcept;

            /// @brief Attempts to retrieve the pad with the index passed.
            /// @param index Index of the pad to retrieve.
            /// @return Optional containing a const reference to the pad, std::nullopt if out of range.
            sdl3::OptionalReference<const sdl3::Gamepad> get_pad_by_index(size_t index) const noexcept;

            /// @brief Attempts to retrieve the pad with the ID passed.
            /// @param id ID of the pad to retrieve.
            /// @return Optional containing const reference to the pad, empty or std::nullopt on failure.
            sdl3::OptionalReference<const sdl3::Gamepad> get_pad_by_id(SDL_JoystickID id) const noexcept;

            /// @brief Runs the manager update routine.
            void update();

            /// @brief Begin.
            PadIter begin();

            /// @brief End.
            PadIter end();

            /// @brief Const begin.
            ConstPadIter begin() const noexcept;

            /// @brief Const end.
            ConstPadIter end() const noexcept;

        private:
            /// @brief Stores whether or not a new gamepad was added to the manager.
            bool m_connect{};

            /// @brief Stores whether or not a pad was disconnected.
            bool m_disconnect{};

            /// @brief Vector of gamepads.
            PadVector m_pads{};

            /// @brief Gets the SDL array of joystick IDs.
            /// @param array Reference to array pointer.
            /// @param count Reference to int to store count to.
            /// @return True on success. False on failure.
            JoystickIDArray get_joystick_id_array(int &count);

            /// @brief Updates the current vector of pads.
            /// @param array Array of ids to check.
            void connect_update_pads(std::span<const SDL_JoystickID> ids);

            /// @brief Purges disconnected controllers from the internal vector.
            void disconnect_pads(std::span<const SDL_JoystickID> ids);

            /// @brief Used multiple places. Returns a const iterator to the pad with the ID passed.
            /// @param id
            /// @return
            ConstPadIter find_by_id(SDL_JoystickID id) const noexcept;
    };
}