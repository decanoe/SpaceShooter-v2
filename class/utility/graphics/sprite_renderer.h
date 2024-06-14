#ifndef _SPRITE_RENDERER_CLASS
#define _SPRITE_RENDERER_CLASS

#include "SDL.h"
#include "./screen.h"
#include "./sprite.h"
#include "./graphic_object.h"
#include "../math/vector2.h"

class SpriteRenderer: GraphicObject
{
protected:
    Vector2 position;
    Sprite sprite;
public:
    SpriteRenderer(Vector2 position);
    ~SpriteRenderer();

    void update(const Screen & screen) const override;
};

#endif