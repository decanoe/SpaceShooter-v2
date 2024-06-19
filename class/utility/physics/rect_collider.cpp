#ifndef _RECT_COLLIDER_CLASS

#include "./rect_collider.h"

RectCollider::RectCollider(Transform* transform, Rect rect) {
    this->transform = transform;
    this->rect = rect;
}

Rect RectCollider::bounding_box() const {
    return this->rect.expand_on_rotation(this->transform->angle);
}
CollideInfo RectCollider::collide(Collider col) const {

}
void RectCollider::draw() const {
    if ((World::debug & DEBUG_COLLIDER) == 0) return;

    SDL_SetRenderDrawColor(Graphics::screen.get_renderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect rect = this->bounding_box().offset(Graphics::world_to_screen(this->transform->position)).to_sdl_frect();
    SDL_RenderDrawRectF(Graphics::screen.get_renderer(), &rect);
}
std::string RectCollider::to_str() const {
    return "RectCollider(transform: \"" + this->transform->name + "\",\t Rect: " + this->rect.to_str() + ")";
};

#endif