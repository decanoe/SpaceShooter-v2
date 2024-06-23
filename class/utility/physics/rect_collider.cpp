#ifndef _RECT_COLLIDER_CLASS

#include "./rect_collider.h"

RectCollider::RectCollider(Transform* transform, Rect rect): Collider(transform) {
    this->rect = rect;
}

Rect RectCollider::bounding_box() const {
    return this->rect.expand_on_rotation(this->transform->global_angle());
}
CollisionInfo RectCollider::collide(Collider* col, Vector2 movement) const {
    Rect box = col->bounding_box().offset(movement);
    if (!box.overlap(this->bounding_box())) return CollisionInfo();

    return CollisionInfo(true, this->bounding_box().intersection(box).center(), (movement.flat() * -1).normalized(), (Collider*)this);
}
void RectCollider::draw() const {
    if ((World::debug & DEBUG_COLLIDER) == 0) return;

    SDL_SetRenderDrawColor(Graphics::screen.get_renderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect rect = this->bounding_box().offset(Graphics::world_to_screen(this->transform->global_position())).to_sdl_frect();
    SDL_RenderDrawRectF(Graphics::screen.get_renderer(), &rect);
}
std::string RectCollider::to_str() const {
    return "RectCollider(transform: \"" + this->transform->name + "\",\t Rect: " + this->rect.to_str() + ")";
};

#endif