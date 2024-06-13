#ifndef _SPRITE_CLASS

#include "./sprite.h"

Sprite::Sprite() {}
Sprite::~Sprite() {
    if (this->texture != NULL) SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}
Sprite Sprite::from_file(std::string path, SDL_Renderer* renderer) {
    Sprite sprite;
    // sprite.texture = IMG_LoadTexture(renderer, "FILE");
    return sprite;
}

void Sprite::blit(SDL_Renderer* renderer, Vector2Int position) const {
    if (this->texture == NULL) return;

    SDL_Rect texture_rect;
    texture_rect.x = position.x;
    texture_rect.y = position.y;
    this->get_size(&texture_rect.w, &texture_rect.h);

    SDL_RenderCopy(renderer, this->texture, NULL, &texture_rect); 
}
void Sprite::get_size(int* width, int* height) const {
    if (this->texture == NULL) return;
    SDL_QueryTexture(this->texture, NULL, NULL, (width == nullptr? NULL : width), (height == nullptr? NULL : height));
}

#endif