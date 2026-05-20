#include "GamepadManager.hpp"

#include <algorithm>
#include <memory>

//                          ---- Construction ----

//                          ---- Public Functions ----

bool sdl3::GamepadManager::new_pad_connected() const noexcept { return m_connect; }

bool sdl3::GamepadManager::pad_disconnected() const noexcept { return m_disconnect; }

size_t sdl3::GamepadManager::pad_count() const noexcept { return m_pads.size(); }

sdl3::OptionalReference<const sdl3::Gamepad> sdl3::GamepadManager::get_pad_by_index(size_t index) const noexcept
{
    if (index >= m_pads.size()) { return std::nullopt; }
    return m_pads[index];
}

sdl3::OptionalReference<const sdl3::Gamepad> sdl3::GamepadManager::get_pad_by_id(SDL_JoystickID id) const noexcept
{
    const auto findPad = find_by_id(id);
    if (findPad == m_pads.end()) { return std::nullopt; }

    return *findPad;
}

void sdl3::GamepadManager::update()
{
    // Get the array of joystick IDs, bail if it's empty.
    int joystickCount{};
    JoystickIDArray joystickIDs = get_joystick_id_array(joystickCount);

    // Span wrapper.
    std::span<const SDL_JoystickID> padSpan{joystickIDs.get(), static_cast<size_t>(joystickCount)};

    // End with connects and updates.
    connect_update_pads(padSpan);

    // Start with disconnects.
    disconnect_pads(padSpan);
}

sdl3::GamepadManager::PadIter sdl3::GamepadManager::begin() { return m_pads.begin(); }

sdl3::GamepadManager::PadIter sdl3::GamepadManager::end() { return m_pads.end(); }

sdl3::GamepadManager::ConstPadIter sdl3::GamepadManager::begin() const noexcept { return m_pads.begin(); }

sdl3::GamepadManager::ConstPadIter sdl3::GamepadManager::end() const noexcept { return m_pads.end(); }

//                          ---- Private Functions ----

sdl3::GamepadManager::JoystickIDArray sdl3::GamepadManager::get_joystick_id_array(int &count)
{ return GamepadManager::JoystickIDArray(SDL_GetJoysticks(&count), SDL_free); }

void sdl3::GamepadManager::connect_update_pads(std::span<const SDL_JoystickID> ids)
{
    // Set this to false to be sure.
    m_connect = false;

    for (const SDL_JoystickID id : ids)
    {
        // Check if it's already initialized.
        const auto findPad = find_by_id(id);
        if (findPad != m_pads.end()) { continue; }

        // Emplace/Init.
        m_pads.emplace_back(id);

        // Register a connect occurred.
        m_connect = true;
    }
}

void sdl3::GamepadManager::disconnect_pads(std::span<const SDL_JoystickID> ids)
{
    // Ensure state.
    m_disconnect = false;

    // This is needed or else this whole thing doesn't work very well.
    if (ids.empty() && !m_pads.empty())
    {
        m_pads.clear();
        m_disconnect = true;
        return;
    }

    // Loop through passed span.
    for (const SDL_JoystickID id : ids)
    {
        // Check if it's found. If it is, just continue. It's good.
        const auto findID = find_by_id(id);
        if (findID != m_pads.end()) { continue; }

        // If it's not, it's been unplugged and needs to be purged.
        m_pads.erase(findID);

        // Register the disconnect.
        m_disconnect = true;
    }
}

sdl3::GamepadManager::ConstPadIter sdl3::GamepadManager::find_by_id(SDL_JoystickID id) const noexcept
{
    auto id_match = [=](const sdl3::Gamepad &pad) { return id == pad.get_id(); };
    return std::find_if(m_pads.begin(), m_pads.end(), id_match);
}