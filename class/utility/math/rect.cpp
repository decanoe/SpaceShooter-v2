#ifndef _RECT_CLASS

#include "./rect.h"

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

Rect Rect::offset(Vector2 offset) const {
    return Rect(this->x + offset.x, this->y + offset.y, this->width, this->height);
}
Rect Rect::expand_on_rotation(float angle) const {
    /*
    A-------B
    |       |
    C-------D
    */

   Vector2 A = this->position().rotate(angle);
   Vector2 B = Vector2(this->x + this->width, this->y).rotate(angle);
   Vector2 C = Vector2(this->x, this->y + this->height).rotate(angle);
   Vector2 D = Vector2(this->x + this->width, this->y + this->height).rotate(angle);

   return Rect().grow_to_fit(A).grow_to_fit(B).grow_to_fit(C).grow_to_fit(D);
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
bool Rect::overlap(Rect rect) const {
    return this->x < rect.x + rect.width
        && this->x + this->width > rect.x
        && this->y < rect.y + rect.height
        && this->y + this->height > rect.y;
}
Rect& Rect::grow_to_fit(Vector2 position) {
    this->x = __min(this->x, position.x);
    this->y = __min(this->y, position.y);

    this->width = __max(this->width, position.x - this->x);
    this->height = __max(this->height, position.y - this->y);

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

std::string Rect::to_str() const {
    return "Rect(" + this->position().to_str() + ", " + this->size().to_str() + ")";
}

#endif