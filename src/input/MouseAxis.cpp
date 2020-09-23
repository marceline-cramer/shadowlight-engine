#include "input/MouseAxis.hpp"

void MouseAxis::updateRelative(int rel)
{
    axis = rel / (float) 100.0;
}

void MouseAxis::process()
{
    // TODO Mouse smoothing
}
