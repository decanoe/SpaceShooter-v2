#ifndef _COMPONENT_CLASS
#define _COMPONENT_CLASS

#include "./transform.h"
class Transform;
class Component
{
public:
    Transform* transform;
    Component(Transform* holder);

    virtual void update() {};
    virtual void release() {};
};


#endif