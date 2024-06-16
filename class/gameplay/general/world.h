#ifndef _WORLD
#define _WORLD

#include <vector>
#include "../../utility/graphics/object_renderer.h"
#include "../../utility/updatable.h"
#include "../../utility/physics/transform.h"

#define DEBUG_FPS 1
#define DEBUG_PHYSICS 2
#define DEBUG_COLLIDER 4

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

    extern std::vector<ObjectRenderer*> object_renderers;
    extern std::vector<Updatable*> update_list;

    Vector2 get_world_center();

    void update(float deltatime);
    void render();
    void release();
}


#endif