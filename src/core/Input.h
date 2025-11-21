#pragma once
#include <SDL2/SDL.h>
#include <iostream>

enum Action {
    left,
    right,
    up,
    down,
    jump,
    crouch,
    none
};

class Input {
public:
    Input() {
        std::cout << "Input class has been instantiated.\n";
    }

    ~Input() {
        std::cout << "Input class has been destroyed.\n";
    }

    void update() {
        // Reset action each frame
        action = none;

        SDL_PumpEvents(); // Update the state of the keyboard
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_W]) action = up;
        else if (state[SDL_SCANCODE_A]) action = left;
        else if (state[SDL_SCANCODE_S]) action = down;
        else if (state[SDL_SCANCODE_D]) action = right;

        std::cout << "Current Action = " << action << "\n";
    }

    Action getAction() const { return action; }

private:
    Action action = none;
};
