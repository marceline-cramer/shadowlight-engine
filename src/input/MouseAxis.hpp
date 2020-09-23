#pragma once

#include "input/InputAxis.hpp"

class MouseAxis : public InputAxis
{
public:
    void updateRelative(int);

    virtual void process(double);
    virtual float getAxis() { return axis; }
private:
    float axis;
};
