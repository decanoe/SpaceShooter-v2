#ifndef _SPRITE_RENDERER_CLASS
#define _SPRITE_RENDERER_CLASS

#include "SDL.h"
#include "./screen.h"
#include "./sprite.h"
#include "./updatable.h"
#include "../math/vector2.h"

class SpriteRenderer: Updatable
{
private:
    Vector2 position;
    Sprite sprite;
public:
    SpriteRenderer(Vector2 position);
    ~SpriteRenderer();

    void update(const Screen & screen) const;
};

#endif