#ifndef _OBJECT_RENDERER_CLASS
#define _OBJECT_RENDERER_CLASS

#include "./screen.h"
#include "../../gameplay/general/graphics.h"
#include "../component/component.h"

class ObjectRenderer: public Component
{
public:
    ObjectRenderer(Transform* transform): Component(transform) {}
    float z_index = 0;
    // false if this instance belongs to another object and should not be deleted
    bool free_object = false;
    virtual void draw() const {}
    virtual void release() {}

    virtual std::string to_str() const { return "ObjectRenderer()"; }
};

#endif