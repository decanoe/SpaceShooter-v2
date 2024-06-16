#ifndef _GRAPHICS

#include "./graphics.h"

Screen Graphics::screen = Screen(true);
SDL_Renderer* Graphics::renderer = Graphics::screen.get_renderer();
Sprite Graphics::sprite_sheet = Sprite("sprites/Ship - parts.png", "sprite_sheet");

Vector2 Graphics::world_to_screen(Vector2 position) {
    return position - World::get_world_center() + Vector2(Graphics::screen.width, Graphics::screen.height) / 2;
}
Vector2 Graphics::screen_to_world(Vector2 position) {
    return position - Vector2(Graphics::screen.width, Graphics::screen.height) / 2 + World::get_world_center();
}

#endif