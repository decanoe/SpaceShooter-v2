#ifndef _WORLD
#define _WORLD

#include <map>
#include <vector>
#include "../../utility/math/vector2.h"
#include "../../utility/component/transform.h"

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
struct CollisionInfo;
class RigidObject;

namespace World
{
    extern unsigned int debug;
    extern float deltatime;

    extern Transform* world_center;
    extern Transform* temp_world_center;
    extern Vector2 temp_world_center_pos;
    extern float temp_world_center_strenght;

    extern std::vector<Transform*> global_object_list;

    extern std::map<Vector2Int, std::vector<Transform*>> object_map;

    Vector2 get_world_center();

    void update(float deltatime);
    void render();
    void world_setup();
    void release();

    template <class T>
    std::vector<T*> get_chunk_content(Vector2Int index);
    Vector2Int get_chunk_index(Vector2 position);
    
    void add_object(Transform* obj);
    void remove_object(Transform* obj);

    CollisionInfo test_collision(RigidObject* rb, Vector2 movement);
}


#endif