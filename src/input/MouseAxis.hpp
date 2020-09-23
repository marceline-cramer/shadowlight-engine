#pragma once

#include "input/InputAxis.hpp"

class MouseAxis : public InputAxis
{
public:
    MouseAxis(double);
    
    void updateRelative(int);

    virtual void process(double);
    virtual float getAxis() { return axis; }
private:
    int rel;
    float axis;

    double sensitivity;
};
