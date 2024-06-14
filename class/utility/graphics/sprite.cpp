#ifndef _SPRITE_CLASS

#include "./sprite.h"
#include "../math/rect.h"

Sprite::Sprite() {}
Sprite::~Sprite() {
    if (this->texture != NULL) SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}
Sprite Sprite::from_file(const char* path, SDL_Renderer* renderer, Vector2Int offset, Vector2Int size) {
    Sprite sprite;

    sprite.texture = IMG_LoadTexture(renderer, path);
    if (sprite.texture == NULL) {
        std::cerr << "cannot convert surface to texture from path \"" << path << "\": " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    sprite.offset = offset;
    sprite.size = size;
    if (sprite.size == Vector2Int()) SDL_QueryTexture(sprite.texture, NULL, NULL, &sprite.size.x, &sprite.size.y);

    return sprite;
}

void Sprite::blit(SDL_Renderer* renderer, Vector2Int position) const {
    if (this->texture == NULL) return;

    SDL_RenderCopy(renderer, this->texture, &Rect(this->offset, this->size).to_sdl_rect(), &Rect(position, this->size).to_sdl_rect());
}
Vector2Int Sprite::get_size() const {
    return this->size;
}

#endif