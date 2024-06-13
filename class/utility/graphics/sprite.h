#ifndef _SPRITE_CLASS
#define _SPRITE_CLASS

#include "SDL.h"
#include "SDL_image.h"
#include "../math/vector2.h"

class Sprite
{
private:
    SDL_Texture* texture = NULL;
public:
    Sprite();
    ~Sprite();
    static Sprite from_file(const char* path, SDL_Renderer* renderer);

    void blit(SDL_Renderer* renderer, Vector2Int position) const;
    void get_size(int* width = nullptr, int* height = nullptr) const;
};

#endif