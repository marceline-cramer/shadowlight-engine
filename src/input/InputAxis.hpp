#pragma once

class InputAxis
{
public:
    virtual ~InputAxis() {}
    
    virtual float getAxis() = 0;
private:
};
