#ifndef _SPRITE_CLASS
#define _SPRITE_CLASS

#include "SDL.h"
#include "SDL_image.h"
#include "../math/vector2.h"
#include "../../gameplay/general/graphics.h"

class Sprite
{
protected:
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    Vector2Int size = Vector2Int();
public:
    std::string name;
    Sprite() {}
    Sprite(const char* path, std::string name = "unnamed Sprite");

    void update_texture();
    void release();
    static Sprite copy(const Sprite& other);
    static Sprite copy(const Sprite& other, Vector2Int new_size);
    static Sprite copy(const Sprite& other, Vector2Int offset, Vector2Int size);
    static Sprite copy(const Sprite& other, Vector2Int offset, Vector2Int size, Vector2Int new_size);

    void blit(Vector2 position, float angle = 0, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
    Vector2Int get_size() const;

    bool is_sprite() const;
    std::string to_str() const;
};

#endif