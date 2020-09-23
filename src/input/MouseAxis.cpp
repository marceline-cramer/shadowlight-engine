#include "input/MouseAxis.hpp"

void MouseAxis::updateRelative(int rel)
{
    axis = rel / (float) 50.0;
}

void MouseAxis::process()
{
    // TODO Mouse smoothing
}
