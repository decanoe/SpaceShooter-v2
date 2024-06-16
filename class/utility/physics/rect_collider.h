#ifndef _RECT_COLLIDER_CLASS
#define _RECT_COLLIDER_CLASS

#include "./collider.h"

class RectCollider: public Collider
{
protected:
    Rect rect;
public:
    RectCollider(Transform* transform, Rect rect);
    RectCollider() {}
    ~RectCollider() {}

    Rect bounding_box() const override;
    CollideInfo collide(Collider col) const override;
    void draw() const override;
    std::string to_str() const override;
};

#endif