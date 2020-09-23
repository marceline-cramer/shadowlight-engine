#pragma once

#include <set>

#include <SDL2/SDL.h>

#include "input/InputAxis.hpp"

class KeyboardAxis;
using KeyboardAxisSet = std::set<KeyboardAxis*>;

class KeyboardAxis : public InputAxis
{
public:
    KeyboardAxis(SDL_Scancode, SDL_Scancode);

    virtual void process();
    virtual float getAxis() { return axis; }
private:
    float axis;

    const Uint8* keys;
    SDL_Scancode negKey;
    SDL_Scancode posKey;
};
