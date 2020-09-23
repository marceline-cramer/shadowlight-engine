#include "input/MouseAxis.hpp"

void MouseAxis::process(int _axis)
{
    axis = _axis / (float) 50.0;
}
