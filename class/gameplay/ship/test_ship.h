#ifndef _TEST_SHIP_CLASS
#define _TEST_SHIP_CLASS

#include "SDL.h"
#include "../../utility/physics/rigid_object.h"
#include "../../utility/physics/rect_collider.h"
#include "../../utility/graphics/sprite_renderer.h"
#include "../general/graphics.h"

class TestShip: public Transform
{
protected:
public:
    RigidObject* rigid_object;
    TestShip(Vector2 position);
    void update() override;

    void manage_event(const SDL_Event& e);
    void manage_continuous_event();
};

#endif