#ifndef _ASTEROID_CLASS
#define _ASTEROID_CLASS

#include "../../utility/physics/rigid_object.h"
#include "../../utility/physics/rect_collider.h"
#include "../../utility/graphics/sprite_renderer.h"
#include "../general/graphics.h"

class Asteroid: public Updatable
{
protected:
public:
    RectCollider rect_collider;
    RigidObject rigid_object;
    SpriteRenderer sprite_renderer;
    Asteroid();

    void update() override;
    void release() override;
    void insert_to_world(bool free_object) override;
    void change_chunk(Vector2Int previous_chunk_index) override;
};

#endif