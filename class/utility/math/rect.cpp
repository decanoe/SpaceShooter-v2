#ifndef _RECT_CLASS

#include "./rect.h"

Rect::Rect() {};
Rect::Rect(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
Rect::Rect(Vector2 position, Vector2 size) {
    this->x = position.x;
    this->y = position.y;
    this->width = size.x;
    this->height = size.y;
}
Rect::Rect(Vector2Int position, Vector2Int size) {
    this->x = position.x;
    this->y = position.y;
    this->width = size.x;
    this->height = size.y;
}
Rect::Rect(float width, float height) {
    this->x = 0;
    this->y = 0;
    this->width = width;
    this->height = height;
}
Rect::Rect(Vector2 size) {
    this->x = 0;
    this->y = 0;
    this->width = size.x;
    this->height = size.y;
}

Rect Rect::recenter(Vector2 new_center) const {
    return Rect(new_center.x - this->width / 2, new_center.y - this->height / 2, this->width, this->height);
}
Rect Rect::offset(Vector2 offset) const {
    return Rect(this->x + offset.x, this->y + offset.y, this->width, this->height);
}
Rect Rect::expand_on_rotation(float angle) const {
    /*
    A-------B
    |       |
    C-------D
    */

   Vector2 center = this->center();

   Vector2 A = center + (Vector2(-this->width, -this->height) / 2).rotate(angle);
   Vector2 B = center + (Vector2( this->width, -this->height) / 2).rotate(angle);
   Vector2 C = center + (Vector2(-this->width,  this->height) / 2).rotate(angle);
   Vector2 D = center + (Vector2( this->width,  this->height) / 2).rotate(angle);

   return Rect(center, Vector2()).grow_to_fit(A).grow_to_fit(B).grow_to_fit(C).grow_to_fit(D);
}

Vector2 Rect::position() const {
    return Vector2(this->x, this->y);
}
Vector2 Rect::center() const {
    return this->position() + this->size() / 2;
}
Vector2 Rect::size() const {
    return Vector2(this->width, this->height);
}

bool Rect::contains(Vector2 point) const {
    return point.x >= this->x
        && point.x <= this->x - this->width
        && point.y >= this->y
        && point.y <= this->y - this->height;
}
Rect Rect::intersection(const Rect& rect) const {
    Vector2 p1;
    Vector2 p2;
    for (int x: {0, 1})
    for (int y: {0, 1})
    {
        if (rect.contains(Vector2(this->x + x * this->width, this->y + y * this->height)))
            p1 = Vector2(this->x + x * this->width, this->y + y * this->height);
        if (this->contains(Vector2(rect.x + x * rect.width, rect.y + y * rect.height)))
            p2 = Vector2(rect.x + x * rect.width, rect.y + y * rect.height);
    }
    return Rect(__min(p1.x, p2.x), __min(p1.y, p2.y), std::abs(p1.x - p2.x), std::abs(p1.y - p2.y));
}
bool Rect::overlap(Rect rect) const {
    return this->x < rect.x + rect.width
        && this->x + this->width > rect.x
        && this->y < rect.y + rect.height
        && this->y + this->height > rect.y;
}
Rect& Rect::grow_to_fit(Vector2 position) {
    float x_w = this->x + this->width;
    float y_h = this->y + this->height;

    this->x = __min(this->x, position.x);
    this->y = __min(this->y, position.y);

    x_w = __max(x_w, position.x);
    y_h = __max(y_h, position.y);

    this->width = x_w - this->x;
    this->height = y_h - this->y;

    return *this;
}

SDL_Rect Rect::to_sdl_rect() const {
    SDL_Rect rect;
    rect.x = this->x;
    rect.y = this->y;
    rect.w = this->width;
    rect.h = this->height;
    return rect;
}
SDL_FRect Rect::to_sdl_frect() const {
    SDL_FRect rect;
    rect.x = this->x;
    rect.y = this->y;
    rect.w = this->width;
    rect.h = this->height;
    return rect;
}

std::string Rect::to_str() const {
    return "Rect(" + this->position().to_str() + ", " + this->size().to_str() + ")";
}

#endif