#include "input/MouseAxis.hpp"

MouseAxis::MouseAxis(double _sensitivity)
{
    sensitivity = _sensitivity;
}

void MouseAxis::updateRelative(int _rel)
{
    rel += _rel;
}

void MouseAxis::process(double dt)
{
    // TODO Mouse smoothing
    axis = (dt * rel) * sensitivity;
    rel = 0;
}
