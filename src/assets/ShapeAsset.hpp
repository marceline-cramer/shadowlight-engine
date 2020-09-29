#pragma once

#include "assets/Asset.hpp"

class ShapeAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();
private:
};
