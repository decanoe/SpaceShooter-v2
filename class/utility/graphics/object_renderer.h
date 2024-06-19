#ifndef _OBJECT_RENDERER_CLASS
#define _OBJECT_RENDERER_CLASS

#include "./screen.h"
#include "../../gameplay/general/graphics.h"

class ObjectRenderer
{
public:
    float z_index = 0;
    // false if this instance belongs to another object and should not be deleted
    bool free_object = false;
    virtual void draw() const {};
    virtual void release() {};

    virtual std::string to_str() const { return "ObjectRenderer()"; }

    // to sort a vector of ObjectRenderer with z_index
    bool operator<(const ObjectRenderer& other) const { return this->z_index < other.z_index; }
};

#endif