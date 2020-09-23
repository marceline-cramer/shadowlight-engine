#pragma once

class InputAxis
{
public:
    virtual ~InputAxis() {}
    
    virtual void process() = 0;
    virtual float getAxis() = 0;
private:
};
