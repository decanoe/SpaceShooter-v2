#ifndef _RECT_COLLIDER_CLASS
#define _RECT_COLLIDER_CLASS

#include "./collider.h"

class RectCollider: public Collider
{
protected:
    Rect rect;
public:
    RectCollider(Transform* transform, Rect rect);
    ~RectCollider() {}

    Rect bounding_box() const override;
    CollisionInfo collide(Collider* col, Vector2 movement) const override;
    void draw() const override;
    std::string to_str() const override;
};

#endif