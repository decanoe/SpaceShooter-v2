#ifndef _RECT_COLLIDER_CLASS

#include "./rect_collider.h"

RectCollider::RectCollider(Transform& transform, Rect rect) {
    this->transform = transform;
    this->rect = rect;
}

Rect RectCollider::bounding_box() const {
    return this->rect.expand_on_rotation(this->transform.angle);
}
CollideInfo RectCollider::collide(Collider col) const {

}

#endif