#ifndef _WORLD
#define _WORLD

#include <map>
#include <vector>
#include "../../utility/graphics/object_renderer.h"
#include "../../utility/updatable.h"
#include "../../utility/physics/transform.h"

#define CHUNK_WIDTH 384
#define RENDER_RADIUS 3
#define UPDATE_RADIUS 5

#define DEBUG_FPS 1
#define DEBUG_PHYSICS 2
#define DEBUG_COLLIDER 4
#define DEBUG_CHUNK 8

#define DEBUG_NONE 0
#define DEBUG_ALL (~0u)

class ObjectRenderer;

namespace World
{
    extern unsigned int debug;
    extern float deltatime;

    extern Transform* world_center;
    extern Transform* temp_world_center;
    extern Vector2 temp_world_center_pos;
    extern float temp_world_center_strenght;

    extern std::vector<ObjectRenderer*> global_renderer_list;
    extern std::vector<Updatable*> global_update_list;

    extern std::map<Vector2Int, std::vector<ObjectRenderer*>> renderer_map;
    extern std::map<Vector2Int, std::vector<Updatable*>> update_map;

    Vector2 get_world_center();

    void update(float deltatime);
    void render();
    void world_setup();
    void release();

    std::vector<Updatable*> get_chunk_content(Vector2Int index);
    std::vector<ObjectRenderer*> get_chunk_render_content(Vector2Int index);
    Vector2Int get_chunk_index(Vector2 position);
    void add_object_renderer(ObjectRenderer* obj, Vector2 position);
    void add_updatable(Updatable* obj, Vector2 position);

    void remove_object_renderer(ObjectRenderer* obj, Vector2Int chunk_index);
    void remove_updatable(Updatable* obj, Vector2Int chunk_index);
}


#endif