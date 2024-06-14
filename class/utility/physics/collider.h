#ifndef _COLLIDER_CLASS
#define _COLLIDER_CLASS

#include "../math/vector2.h"
#include "../math/rect.h"
#include "./transform.h"

struct CollideInfo
{
    bool hit;
    Vector2 position;
    Vector2 normal;
};


class Collider
{
protected:
    Transform& transform;
public:
    Collider(); // prevents Intellisense bug

    virtual Rect bounding_box() const;
    virtual CollideInfo collide(Collider col) const;
};

#endif