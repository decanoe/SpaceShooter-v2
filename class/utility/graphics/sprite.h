#ifndef _SPRITE_CLASS
#define _SPRITE_CLASS

#include "SDL.h"
#include "SDL_image.h"
#include "../math/vector2.h"

class Sprite
{
protected:
    SDL_Texture* texture = NULL;
    Vector2Int offset;
    Vector2Int size;
public:
    Sprite();
    ~Sprite();
    static Sprite from_file(const char* path, SDL_Renderer* renderer, Vector2Int offset = Vector2Int(), Vector2Int size = Vector2Int());

    void blit(SDL_Renderer* renderer, Vector2Int position) const;
    Vector2Int get_size() const;
};

#endif