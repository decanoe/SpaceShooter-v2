#ifndef _WORLD

#include <algorithm>
#include "./world.h"
#include "../../utility/math/random_generator.h"

#include "../effect/stars.h"
#include "../objects/asteroid.h"

unsigned int World::debug = DEBUG_ALL;
float World::deltatime = 1.0/60;
std::vector<ObjectRenderer*> World::global_renderer_list = std::vector<ObjectRenderer*>();
std::vector<Updatable*> World::global_update_list = std::vector<Updatable*>();

std::map<Vector2Int, std::vector<ObjectRenderer*>> World::renderer_map = std::map<Vector2Int, std::vector<ObjectRenderer*>>();
std::map<Vector2Int, std::vector<Updatable*>> World::update_map = std::map<Vector2Int, std::vector<Updatable*>>();

void World::world_setup() {
    Stars* stars = new Stars(256);
    stars->free_object = true;
    World::global_renderer_list.push_back(stars);

    for (int i = 0; i < 128; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->position = Random::get_vect2_in_circle(Vector2(), 1024);
        asteroid->insert_to_world(true);
    }
}
void World::update(float deltatime) {
    World::deltatime = deltatime;
    for (Updatable* obj : World::global_update_list)
    {
        obj->update();
    }

    Vector2Int central_chunk = World::get_chunk_index(World::get_world_center());
    for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
    for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++)
    for (Updatable* obj : World::get_chunk_content(Vector2Int(x, y)))
    {
        obj->update();
    }

    for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
    for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++)
    for (Updatable* obj : World::get_chunk_content(Vector2Int(x, y)))
    {
        if (World::get_chunk_index(obj->position) != Vector2Int(x, y)) obj->change_chunk(Vector2Int(x, y));
    }
}
void World::render() {
    SDL_SetRenderTarget(Graphics::renderer, NULL);
    SDL_SetRenderDrawColor(Graphics::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Graphics::renderer);

    Vector2Int central_chunk = World::get_chunk_index(World::get_world_center());
    if (World::debug & DEBUG_CHUNK) {
        SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
        for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++)
        {
            SDL_FRect rect = Rect(Graphics::world_to_screen(Vector2(x, y) * CHUNK_WIDTH), Vector2(CHUNK_WIDTH, CHUNK_WIDTH)).to_sdl_frect();
            SDL_RenderDrawRectF(Graphics::renderer, &rect);
        }
        SDL_SetRenderDrawColor(Graphics::renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        for (int x = central_chunk.x - RENDER_RADIUS; x <= central_chunk.x + RENDER_RADIUS; x++)
        for (int y = central_chunk.y - RENDER_RADIUS; y <= central_chunk.y + RENDER_RADIUS; y++)
        {
            SDL_FRect rect = Rect(Graphics::world_to_screen(Vector2(x * CHUNK_WIDTH + 1, y * CHUNK_WIDTH + 1)), Vector2(CHUNK_WIDTH - 2, CHUNK_WIDTH - 2)).to_sdl_frect();
            SDL_RenderDrawRectF(Graphics::renderer, &rect);
        }
    }
    
    std::vector<ObjectRenderer*> renderers = std::vector<ObjectRenderer*>(World::global_renderer_list);

    for (int x = central_chunk.x - RENDER_RADIUS; x <= central_chunk.x + RENDER_RADIUS; x++)
    for (int y = central_chunk.y - RENDER_RADIUS; y <= central_chunk.y + RENDER_RADIUS; y++)
    for (ObjectRenderer* obj : World::get_chunk_render_content(Vector2Int(x, y)))
    {
        renderers.push_back(obj);
    }

    std::sort(renderers.begin(), renderers.end());
    for (ObjectRenderer* obj : renderers)
    {
        obj->draw();
    }
    renderers.clear();
    
    Graphics::sprite_sheet.blit(Vector2Int(512, 0));
    Graphics::screen.update();
}
void World::release() {
    for (ObjectRenderer* obj : World::global_renderer_list)
    {
        obj->release();
        if (obj->free_object) delete obj;
    }
    World::global_renderer_list.clear();

    for (auto const& [chunk_index, chunk_content] : World::renderer_map) {
        for (ObjectRenderer* obj : chunk_content)
        {
            obj->release();
            if (obj->free_object) delete obj;
        }
    }
    World::renderer_map.clear();


    for (Updatable* obj : World::global_update_list)
    {
        obj->release();
        if (obj->free_object) delete obj;
    }
    World::global_update_list.clear();

    for (auto const& [chunk_index, chunk_content] : World::update_map) {
        for (Updatable* obj : chunk_content)
        {
            obj->release();
            if (obj->free_object) delete obj;
        }
    }
    World::update_map.clear();
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

std::vector<Updatable*> World::get_chunk_content(Vector2Int index) {
    if (!World::update_map.count(index)) return std::vector<Updatable*>();
    return World::update_map[index];
}
std::vector<ObjectRenderer*> World::get_chunk_render_content(Vector2Int index) {
    if (!World::renderer_map.count(index)) return std::vector<ObjectRenderer*>();
    return World::renderer_map[index];
}
Vector2Int World::get_chunk_index(Vector2 position) {
    return (position / CHUNK_WIDTH).floor();
}

void World::add_object_renderer(ObjectRenderer* obj, Vector2 position) {
    Vector2Int chunk = World::get_chunk_index(position);

    if (!World::renderer_map.count(chunk)) World::renderer_map[chunk] = std::vector<ObjectRenderer*>();
    World::renderer_map[chunk].push_back(obj);
}
void World::add_updatable(Updatable* obj, Vector2 position) {
    Vector2Int chunk = World::get_chunk_index(position);

    if (!World::update_map.count(chunk)) World::update_map[chunk] = std::vector<Updatable*>();
    World::update_map[chunk].push_back(obj);
}

void World::remove_object_renderer(ObjectRenderer* obj, Vector2Int chunk_index) {
    if (!World::renderer_map.count(chunk_index)) {
        std::cerr << "ERROR: trying to remove \"" << obj->to_str() << "\" from chunk " << chunk_index.to_str() << ", chunk not found !\n";
        exit(EXIT_FAILURE);
    }

    if (std::find(World::renderer_map[chunk_index].begin(), World::renderer_map[chunk_index].end(), obj) == World::renderer_map[chunk_index].end()) {
        std::cerr << "ERROR: trying to remove \"" << obj->to_str() << "\" from chunk " << chunk_index.to_str() << ", object not found !\n";
        exit(EXIT_FAILURE);
    }

    World::renderer_map[chunk_index].erase(std::remove(World::renderer_map[chunk_index].begin(), World::renderer_map[chunk_index].end(), obj), World::renderer_map[chunk_index].end());
}
void World::remove_updatable(Updatable* obj, Vector2Int chunk_index) {
    if (!World::update_map.count(chunk_index)) {
        std::cerr << "ERROR: trying to remove updatable from chunk " << chunk_index.to_str() << ", chunk not found !\n";
        exit(EXIT_FAILURE);
    }

    if (std::find(World::update_map[chunk_index].begin(), World::update_map[chunk_index].end(), obj) == World::update_map[chunk_index].end()) {
        std::cerr << "ERROR: trying to remove an updatable from chunk " << chunk_index.to_str() << ", updatable not found !\n";
        exit(EXIT_FAILURE);
    }

    World::update_map[chunk_index].erase(std::remove(World::update_map[chunk_index].begin(), World::update_map[chunk_index].end(), obj), World::update_map[chunk_index].end());
}
#endif