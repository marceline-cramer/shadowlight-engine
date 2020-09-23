#pragma once

#include "input/InputAxis.hpp"

class MouseAxis : public InputAxis
{
public:
    void updateRelative(int);

    virtual void process();
    virtual float getAxis() { return axis; }
private:
    float axis;
};
