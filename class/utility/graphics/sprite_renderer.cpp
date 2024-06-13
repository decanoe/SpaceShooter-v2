#ifndef _SPRITE_RENDERER_CLASS

#include "./sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Vector2 position)
{
    this->position = position;
}

void SpriteRenderer::update(const Screen& screen) const {
    this->sprite.blit(screen.get_renderer(), this->position.round());
}


#endif