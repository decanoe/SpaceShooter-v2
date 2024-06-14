#ifndef _RECT_CLASS
#define _RECT_CLASS

#include <iostream>
#include <string>
#include <cmath>

#include "SDL.h"
#include "./vector2.h"

class Rect
{
private:
public:
    float x = 0, y = 0, width = 0, height = 0;

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(Vector2 position, Vector2 size);
    Rect(Vector2Int position, Vector2Int size);

    Rect offset(Vector2 offset) const;
    Rect expand_on_rotation(float angle) const;

    Vector2 position() const;
    Vector2 center() const;
    Vector2 size() const;

    // returns true if a given point is inside or in the boundaries of this rect
    bool contains(Vector2 point) const;
    // returns true if the given rect overlaps this one
    bool overlap(Rect rect) const;
    // grows the rect in place to fit a given point and returns itself
    Rect& grow_to_fit(Vector2 position);

    // returns a SDL representation of a rect
    SDL_Rect to_sdl_rect() const;

    // returns a string in the format "Rect(Vector2(x, y), Vector2(width, height))"
    std::string to_str() const;
};

#endif