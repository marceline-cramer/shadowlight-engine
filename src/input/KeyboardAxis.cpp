#include "input/KeyboardAxis.hpp"

KeyboardAxis::KeyboardAxis(SDL_Scancode _negKey, SDL_Scancode _posKey)
{
    keys = SDL_GetKeyboardState(nullptr);
    negKey = _negKey;
    posKey = _posKey;
}

void KeyboardAxis::process(double dt)
{
    if(keys[negKey]) {
        if(keys[posKey]) {
            axis = 0.0;
        } else {
            axis = -1.0;
        }
    } else {
        if(keys[posKey]) {
            axis = 1.0;
        } else {
            axis = 0.0;
        }
    }
}
