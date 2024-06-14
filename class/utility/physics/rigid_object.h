#ifndef _RIGID_OBJECT_CLASS
#define _RIGID_OBJECT_CLASS

#include "../math/vector2.h"
#include "./transform.h"
#include "./collider.h"

class RigidObject
{
protected:
    Transform& transform;
    Transform& Collider;
    Vector2 velocity = Vector2();
public:
    RigidObject(Transform& transform, Transform& Collider);
    ~RigidObject();

    void update(float deltatime);
};


#endif