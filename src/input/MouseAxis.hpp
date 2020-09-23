#pragma once

#include "input/InputAxis.hpp"

class MouseAxis : public InputAxis
{
public:
    void process(int);

    virtual float getAxis() { return axis; }
private:
    float axis;
};
