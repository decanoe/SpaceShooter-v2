#ifndef _SPRITE_RENDERER_CLASS
#define _SPRITE_RENDERER_CLASS

#include "SDL.h"
#include "./screen.h"
#include "./sprite.h"
#include "./object_renderer.h"
#include "../math/vector2.h"

class SpriteRenderer: public ObjectRenderer
{
public:
    Sprite sprite;
    SpriteRenderer(Transform* transform, Sprite sprite);
    void release() override;

    void draw() const override;
    std::string to_str() const override;
};

#endif