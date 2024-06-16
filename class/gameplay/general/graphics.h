#ifndef _GRAPHICS
#define _GRAPHICS

#include "../../utility/graphics/screen.h"
#include "../../utility/graphics/sprite.h"
#include "./world.h"
class Sprite;

namespace Graphics
{
    extern SDL_Renderer* renderer;
    extern Screen screen;
    extern Sprite sprite_sheet;

    Vector2 world_to_screen(Vector2 position);
    Vector2 screen_to_world(Vector2 position);
}

#endif