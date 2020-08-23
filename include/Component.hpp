#pragma once

class Component
{
public:
    virtual ~Component() {};
    virtual void update() = 0;
    virtual const char* getComponentType() = 0;
private:
};
