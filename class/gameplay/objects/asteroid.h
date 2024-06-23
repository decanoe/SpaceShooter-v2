#ifndef _ASTEROID_CLASS
#define _ASTEROID_CLASS

#include "../../utility/physics/rigid_object.h"
#include "../../utility/physics/rect_collider.h"
#include "../../utility/graphics/sprite_renderer.h"
#include "../general/graphics.h"

class Asteroid: public Transform
{
protected:
public:
    Asteroid(Transform* parent = nullptr);
};

#endif