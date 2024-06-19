#ifndef _TEST_SHIP_CLASS
#define _TEST_SHIP_CLASS

#include "SDL.h"
#include "../../utility/physics/rigid_object.h"
#include "../../utility/physics/rect_collider.h"
#include "../../utility/graphics/sprite_renderer.h"
#include "../general/graphics.h"

class TestShip: public Updatable
{
protected:
public:
    RectCollider rect_collider;
    RigidObject rigid_object;
    SpriteRenderer sprite_renderer;
    TestShip(Vector2 position);
    void update() override;
    void release() override;
    void insert_to_world(bool free_object) override;
    void change_chunk(Vector2Int previous_chunk_index) override;

    void manage_event(const SDL_Event& e);
    void manage_continuous_event();
};

#endif