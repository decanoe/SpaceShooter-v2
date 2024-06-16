#ifndef _COLLIDER_CLASS
#define _COLLIDER_CLASS

#include "../math/vector2.h"
#include "../math/rect.h"
#include "./transform.h"
#include "../graphics/object_renderer.h"

#include "../../gameplay/general/world.h"

struct CollideInfo
{
    bool hit;
    Vector2 position;
    Vector2 normal;
};


class Collider: public ObjectRenderer
{
protected:
    Transform* transform = nullptr;
public:
    Collider() {}
    ~Collider() {}

    virtual Rect bounding_box() const { return Rect(); };
    virtual CollideInfo collide(Collider col) const { return {false}; };
    virtual std::string to_str() const { return "Collider(transform: \"" + this->transform->name + "\")"; };
};

#endif