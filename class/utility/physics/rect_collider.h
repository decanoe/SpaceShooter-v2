#ifndef _RECT_COLLIDER_CLASS
#define _RECT_COLLIDER_CLASS

#include "./collider.h"
#include "../math/rect.h"

class RectCollider: Collider
{
protected:
    Rect rect;
public:
    RectCollider(Transform& transform, Rect rect);
    ~RectCollider();

    Rect bounding_box() const override;
    CollideInfo collide(Collider col) const override;
};

#endif