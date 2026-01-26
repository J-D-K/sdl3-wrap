#pragma once
#include "states/BaseState.hpp"

#include <memory>
#include <stack>

class StateManager final
{
    public:
        // No copying or moving.
        StateManager(const StateManager &)            = delete;
        StateManager(StateManager &&)                 = delete;
        StateManager &operator=(const StateManager &) = delete;
        StateManager &operator=(StateManager &&)      = delete;

        /// @brief Templated function to create and push a new state.
        /// @tparam StateType Type of state to push.
        /// @tparam ...Args Arguments to forward to constructor of state.
        template <typename StateType, typename... Args>
        static void create_push_state(Args &&...args)
        {
            // Assert the StateType is derived from BaseState.
            static_assert(std::derived_from<StateType, states::BaseState> == true,
                          "Error: State is not derived from BaseState");

            // Get instance.
            StateManager &instance = StateManager::get_instance();

            // Reference to stack.
            auto &stateStack = instance.m_states;

            // Create and push.
            stateStack.push(std::make_unique<StateType>(std::forward<Args>(args)...));
        }

        // State update routine.
        static void update(const sdl3::Input &input)
        {
            // Instance.
            StateManager &instance = StateManager::get_instance();

            // Stack
            auto &stateStack = instance.m_states;

            // Return if the stack is empty.
            if (stateStack.empty()) { return; }

            // Update the top.
            stateStack.top()->update(input);
        }

        // State render routine.
        static void render(sdl3::Renderer &renderer)
        {
            // Instance.
            StateManager &instance = StateManager::get_instance();

            // Stack.
            auto &stateStack = instance.m_states;

            // Return on empty.
            if (stateStack.empty()) { return; }

            // Render the top.
            stateStack.top()->render(renderer);
        }

    private:
        /// @brief Stack of states.
        std::stack<std::unique_ptr<states::BaseState>> m_states;

        /// @brief Private constructor.
        StateManager() = default;

        /// @brief Returns the instance.
        static StateManager &get_instance()
        {
            static StateManager instance;
            return instance;
        }
};