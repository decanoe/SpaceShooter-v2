#ifndef _SPRITE_CLASS

#include "./sprite.h"
#include "../math/rect.h"

Sprite::Sprite(const char* path, std::string name) {
    this->name = name;
    this->surface = IMG_Load(path);
    if (this->surface == NULL) {
        std::cerr << "cannot convert surface to texture from path \"" << path << "\" (name: \"" << name << "\"): " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    this->update_texture();

    this->size = size;
    if (this->size == Vector2Int()) this->size = Vector2Int(this->surface->w, this->surface->h);
}
void Sprite::release() {
    #ifdef _DEBUG_PRINTS
    std::cout << "freeing sprite: " << this->to_str() << "\n";
    #endif

    if (this->surface != NULL) SDL_FreeSurface(this->surface);
    this->surface = NULL;

    if (this->texture != NULL) SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}
void Sprite::update_texture() {
    if (this->texture != NULL) SDL_DestroyTexture(this->texture);
    this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, this->surface);
}

Sprite Sprite::copy(const Sprite& other) { return Sprite::copy(other, Vector2Int(0, 0), other.size, other.size); }
Sprite Sprite::copy(const Sprite& other, Vector2Int new_size) { return Sprite::copy(other, Vector2Int(0, 0), other.size, new_size); }
Sprite Sprite::copy(const Sprite& other, Vector2Int offset, Vector2Int size) { return Sprite::copy(other, offset, size, size); }
Sprite Sprite::copy(const Sprite& other, Vector2Int offset, Vector2Int size, Vector2Int new_size) {
    Sprite sprite;

    sprite.size = new_size;

    sprite.surface = SDL_CreateRGBSurface(0, new_size.x, new_size.y, other.surface->format->BitsPerPixel, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    SDL_BlendMode blend_mode;
    SDL_GetSurfaceBlendMode(other.surface, &blend_mode);
    SDL_SetSurfaceBlendMode(sprite.surface, blend_mode);
    
    SDL_Rect src_rect = Rect(offset, size).to_sdl_rect();
    SDL_Rect dest_rect = Rect(Vector2Int(0, 0), new_size).to_sdl_rect();

    if (SDL_BlitScaled(other.surface, &src_rect, sprite.surface, &dest_rect) == -1) {
        std::cerr << "unable to blit image on copy: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
    sprite.update_texture();

    if (size != other.get_size()) {
        sprite.name = other.name + " offset(" +
            std::to_string(offset.x) + "|" +
            std::to_string(offset.y) + ")";
    }
    else sprite.name = other.name + " copy";

    return sprite;
}

void Sprite::blit(Vector2 position, float angle, SDL_RendererFlip flip) const {
    if (this->texture == NULL) return;

    SDL_FRect dest_rect = Rect(position, (Vector2)this->size).to_sdl_frect();

    SDL_RenderCopyExF(Graphics::renderer, this->texture, NULL, &dest_rect, -angle * 180 / PI, NULL, flip);
}
Vector2Int Sprite::get_size() const {
    return this->size;
}
bool Sprite::is_sprite() const {
    return this->surface != NULL;
}
std::string Sprite::to_str() const {
    if (this->surface == NULL && this->texture == NULL) return "Sprite(name: \"" + this->name + "\",\t size: " + this->size.to_str() + ",\t RELEASED)";

    std::string a1 = std::to_string((unsigned long long)(void**)this->surface);
    std::string a2 = std::to_string((unsigned long long)(void**)this->texture);
    return "Sprite(name: \"" + this->name + "\",\t size: " + this->size.to_str() + ",\t surface: " + (this->surface == NULL?"NULL": a1) + ",\t texture: " + (this->texture == NULL?"NULL":a2) + ")";
}
#endif