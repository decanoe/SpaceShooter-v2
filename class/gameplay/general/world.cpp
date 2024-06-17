#ifndef _WORLD

#include "./world.h"
#include "../effect/stars.h"

unsigned int World::debug = DEBUG_ALL;
float World::deltatime = 1.0/60;
std::vector<ObjectRenderer*> World::object_renderers = std::vector<ObjectRenderer*>();
std::vector<Updatable*> World::update_list = std::vector<Updatable*>();

void World::world_setup() {
    Stars* stars = new Stars(256);
    stars->free_object = true;
    World::object_renderers.push_back(stars);
}
void World::update(float deltatime) {
    World::deltatime = deltatime;
    for (Updatable* obj : World::update_list)
    {
        obj->update();
    }
}
void World::render() {
    SDL_SetRenderTarget(Graphics::renderer, NULL);
    SDL_SetRenderDrawColor(Graphics::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Graphics::renderer);
    for (ObjectRenderer* obj : World::object_renderers)
    {
        obj->draw();
    }
    Graphics::sprite_sheet.blit(Vector2Int(512, 0));
    Graphics::screen.update();
}
void World::release() {
    for (ObjectRenderer* obj : World::object_renderers)
    {
        obj->release();
        if (obj->free_object) delete obj;
    }
    World::object_renderers.clear();

    for (Updatable* obj : World::update_list)
    {
        obj->release();
        if (obj->free_object) delete obj;
    }
    World::update_list.clear();
}

Transform* World::world_center = nullptr;
Transform* World::temp_world_center = nullptr;
Vector2 World::temp_world_center_pos = Vector2();
float World::temp_world_center_strenght = 0;

Vector2 World::get_world_center() {
    if (World::world_center == nullptr) return Vector2();
    if (World::temp_world_center_strenght <= 0) return World::world_center->position;
    
    if (World::temp_world_center != nullptr) World::temp_world_center_pos = World::temp_world_center->position;
    
    return Vector2::Lerp(World::world_center->position, World::temp_world_center_pos, __min(World::temp_world_center_strenght, 1));
    
    World::temp_world_center_strenght -= deltatime;
}

#endif