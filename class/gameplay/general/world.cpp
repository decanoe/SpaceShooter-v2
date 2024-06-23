#ifndef _WORLD

#include <algorithm>
#include "./world.h"
#include "../../utility/math/random_generator.h"
#include "../../utility/physics/collider.h"
#include "../../utility/physics/rigid_object.h"
#include "../../utility/graphics/object_renderer.h"

#include "../effect/stars_renderer.h"
#include "../objects/asteroid.h"
#include <typeinfo>

bool compareRenderers(ObjectRenderer* a, ObjectRenderer* b) { return a->z_index < b->z_index || (a->z_index == b->z_index && a < b); }

unsigned int World::debug = DEBUG_ALL;
float World::deltatime = 1.0/60;
std::vector<Transform*> World::global_object_list = std::vector<Transform*>();
std::map<Vector2Int, std::vector<Transform*>> World::object_map = std::map<Vector2Int, std::vector<Transform*>>();

void World::world_setup() {
    Transform* transform = new Transform("stars");
    transform->components.push_back(new StarsRenderer(256));
    World::global_object_list.push_back(transform);

    for (int i = 0; i < 128; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->local_position = Random::get_vect2_in_circle(Vector2(), 1024);

        World::add_object(asteroid);
    }
}
void World::update(float deltatime) {
    World::deltatime = deltatime;
    for (Transform* obj : World::global_object_list) obj->update();

    Vector2Int central_chunk = World::get_chunk_index(World::get_world_center());
    for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
    for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++) {
        if (!World::object_map.count(Vector2Int(x, y))) continue;
        for (Transform* obj : World::object_map[Vector2Int(x, y)]) obj->update();
    }

    for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
    for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++) {
        if (!World::object_map.count(Vector2Int(x, y))) continue;

        for (Transform* obj : World::object_map[Vector2Int(x, y)])
        {
            if (World::get_chunk_index(obj->root_position()) == Vector2Int(x, y)) continue;

            World::object_map[Vector2Int(x, y)].erase(std::remove(World::object_map[Vector2Int(x, y)].begin(), World::object_map[Vector2Int(x, y)].end(), obj), World::object_map[Vector2Int(x, y)].end());
            World::add_object(obj);
        }
    }
}
void World::render() {
    SDL_SetRenderTarget(Graphics::renderer, NULL);
    SDL_SetRenderDrawColor(Graphics::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Graphics::renderer);

    Vector2Int central_chunk = World::get_chunk_index(World::get_world_center());
    if (World::debug & DEBUG_CHUNK) {
        SDL_SetRenderDrawColor(Graphics::renderer, 0, 0, 200, SDL_ALPHA_OPAQUE);
        for (int x = central_chunk.x - UPDATE_RADIUS; x <= central_chunk.x + UPDATE_RADIUS; x++)
        for (int y = central_chunk.y - UPDATE_RADIUS; y <= central_chunk.y + UPDATE_RADIUS; y++)
        {
            SDL_FRect rect = Rect(Graphics::world_to_screen(Vector2(x, y) * CHUNK_WIDTH), Vector2(CHUNK_WIDTH + 1, CHUNK_WIDTH + 1)).to_sdl_frect();
            SDL_RenderDrawRectF(Graphics::renderer, &rect);
        }
        SDL_SetRenderDrawColor(Graphics::renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        for (int x = central_chunk.x - RENDER_RADIUS; x <= central_chunk.x + RENDER_RADIUS; x++)
        for (int y = central_chunk.y - RENDER_RADIUS; y <= central_chunk.y + RENDER_RADIUS; y++)
        {
            SDL_FRect rect = Rect(Graphics::world_to_screen(Vector2(x * CHUNK_WIDTH + 1, y * CHUNK_WIDTH + 1)), Vector2(CHUNK_WIDTH - 1, CHUNK_WIDTH - 1)).to_sdl_frect();
            SDL_RenderDrawRectF(Graphics::renderer, &rect);
        }
    }

    std::vector<ObjectRenderer*> renderers = std::vector<ObjectRenderer*>();
    for (Transform* obj : World::global_object_list)
    for (ObjectRenderer* r : obj->get_components<ObjectRenderer>())
    {
        renderers.push_back(r);
    }
    
    for (int x = central_chunk.x - RENDER_RADIUS; x <= central_chunk.x + RENDER_RADIUS; x++)
    for (int y = central_chunk.y - RENDER_RADIUS; y <= central_chunk.y + RENDER_RADIUS; y++) {
        if (!World::object_map.count(Vector2Int(x, y))) continue;
        for (Transform* obj : World::object_map[Vector2Int(x, y)])
        for (ObjectRenderer* r : obj->get_components<ObjectRenderer>())
        {
            renderers.push_back(r);
        }
    }

    std::sort(renderers.begin(), renderers.end(), compareRenderers);
    for (ObjectRenderer* obj : renderers)
    {
        obj->draw();
    }
    renderers.clear();
    
    Graphics::sprite_sheet.blit(Vector2Int(512, 0));
    Graphics::screen.update();
}
void World::release() {
    for (Transform* obj : World::global_object_list)
    {
        obj->release();
        delete obj;
    }
    World::global_object_list.clear();

    for (auto const& [chunk_index, chunk_content] : World::object_map) {
        for (Transform* obj : chunk_content)
        {
            obj->release();
            delete obj;
        }
    }
    World::object_map.clear();
}

Transform* World::world_center = nullptr;
Transform* World::temp_world_center = nullptr;
Vector2 World::temp_world_center_pos = Vector2();
float World::temp_world_center_strenght = 0;

Vector2 World::get_world_center() {
    if (World::world_center == nullptr) return Vector2();
    if (World::temp_world_center_strenght <= 0) return World::world_center->global_position();
    
    if (World::temp_world_center != nullptr) World::temp_world_center_pos = World::temp_world_center->global_position();
    
    return Vector2::Lerp(World::world_center->global_position(), World::temp_world_center_pos, __min(World::temp_world_center_strenght, 1));
    
    World::temp_world_center_strenght -= deltatime;
}

template <>
std::vector<Transform*> World::get_chunk_content<Transform>(Vector2Int index) {
    if (!World::object_map.count(index)) return std::vector<Transform*>();
    return World::object_map[index];
}
template <class T>
std::vector<T*> World::get_chunk_content(Vector2Int index) {

    std::vector<T*> result = std::vector<T*>();
    for (Transform* obj : World::global_object_list)
    for (T* c : obj->get_components<T>())
    {
        result.push_back(c);
    }

    if (!World::object_map.count(index)) return result;
    for (Transform* obj : World::object_map[index])
    for (T* c : obj->get_components<T>())
    {
        result.push_back(c);
    }
    return result;
}
Vector2Int World::get_chunk_index(Vector2 position) {
    return (position / CHUNK_WIDTH).floor();
}

void World::add_object(Transform* obj) {
    Vector2Int chunk = World::get_chunk_index(obj->root_position());

    if (!World::object_map.count(chunk)) World::object_map[chunk] = std::vector<Transform*>();
    World::object_map[chunk].push_back(obj);
}
void World::remove_object(Transform* obj) {
    Vector2Int chunk = World::get_chunk_index(obj->root_position());

    if (!World::object_map.count(chunk)) {
        std::cerr << "ERROR: trying to remove \"" << obj->to_str() << "\" from chunk " << chunk.to_str() << ", chunk not found !\n";
        exit(EXIT_FAILURE);
    }

    if (std::find(World::object_map[chunk].begin(), World::object_map[chunk].end(), obj) == World::object_map[chunk].end()) {
        std::cerr << "ERROR: trying to remove \"" << obj->to_str() << "\" from chunk " << chunk.to_str() << ", object not found !\n";
        exit(EXIT_FAILURE);
    }

    World::object_map[chunk].erase(std::remove(World::object_map[chunk].begin(), World::object_map[chunk].end(), obj), World::object_map[chunk].end());
}

CollisionInfo World::test_collision(RigidObject* rb, Vector2 movement) {
    Vector2Int central_chunk = World::get_chunk_index(rb->transform->global_position());
    for (int x: {central_chunk.x, central_chunk.x - 1, central_chunk.x + 1})
    for (int y: {central_chunk.y, central_chunk.y - 1, central_chunk.y + 1}) {
        if (!World::object_map.count(Vector2Int(x, y))) continue;

        for (Collider* col2: World::get_chunk_content<Collider>(Vector2Int(x, y)))
        {
            if (col2->transform == rb->transform) continue;
            if (col2->transform->get_component<RigidObject>() != nullptr && !Physics::do_collide(col2->transform->get_component<RigidObject>()->layer, rb->layer)) continue;
            
            for (Collider* col1: rb->transform->get_components<Collider>())
            {
                CollisionInfo info = col2->collide(col1, movement);
                if (info.hit) return info;
            }
        }
    }
    return CollisionInfo();
}
#endif