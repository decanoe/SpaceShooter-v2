#ifndef _SPRITE_RENDERER_CLASS

#include "./sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Transform* transform, Sprite sprite): ObjectRenderer(transform) {
    this->sprite = sprite;
}
void SpriteRenderer::release() {
    this->sprite.release();
}

void SpriteRenderer::draw() const {
    this->sprite.blit(Graphics::world_to_screen(this->transform->global_position()) - this->sprite.get_size() / 2, this->transform->global_angle());
}

std::string SpriteRenderer::to_str() const {
    return "SpriteRenderer(transform: \"" + this->transform->name + "\")";
    // return "SpriteRenderer(transform: \"" + this->transform->name + "\",\t sprite: \"" + this->sprite.name + "\")";
}


#endif