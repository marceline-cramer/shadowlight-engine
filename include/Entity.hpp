#pragma once

#include <set>

class Entity
{
public:
    void update();
private:
    Entity* parent;
    std::set<Entity*> children;
};
