#ifndef _COLLIDER_CLASS
#define _COLLIDER_CLASS

#include "../graphics/object_renderer.h"
#include "../../gameplay/general/world.h"
#include "../math/vector2.h"
#include "../math/rect.h"

class Collider;
struct CollisionInfo
{
    bool hit;
    Vector2 position;
    Vector2 normal;
    Collider* collider;
    CollisionInfo(bool hit = false, Vector2 position = Vector2(), Vector2 normal = Vector2(), Collider* collider = nullptr) {
        this->hit = hit;
        this->position = position;
        this->normal = normal;
        this->collider = collider;
    }
};


class Collider: public ObjectRenderer
{
public:
    Collider(Transform* transform): ObjectRenderer(transform) {};
    ~Collider() {}

    virtual Rect bounding_box() const { return Rect(); };
    virtual CollisionInfo collide(Collider* col, Vector2 movement) const { return CollisionInfo(false); };
    virtual std::string to_str() const { return "Collider(transform: \"" + this->transform->name + "\")"; };
};

#endif