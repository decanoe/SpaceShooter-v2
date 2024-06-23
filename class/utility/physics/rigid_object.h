#ifndef _RIGID_OBJECT_CLASS
#define _RIGID_OBJECT_CLASS

#include "../math/vector2.h"
#include "../component/component.h"
#include "./collider.h"

namespace Physics {
    enum PhysicsLayer {
        Garbage, Terrain, Ship, None
    };
    bool do_collide(PhysicsLayer a, PhysicsLayer b);
}

class RigidObject: public Component
{
protected:
    Vector2 velocity = Vector2();
    float mass = 500;
    float angle_velocity = 0;
public:
    Physics::PhysicsLayer layer = Physics::PhysicsLayer::None;
    RigidObject(Transform* transform, float mass = 500, Physics::PhysicsLayer layer = Physics::PhysicsLayer::None);
    ~RigidObject() {}

    void update() override;
    void add_force(Vector2 force);
    void add_rotation(float force);
    
    void set_velocity(Vector2 velocity = Vector2());
    Vector2 get_velocity() const;
    void set_angle_velocity(float angle_velocity = 0);
    float get_angle_velocity() const;
    void set_mass(float mass);
    float get_mass() const;

    std::string to_str() const;
};


#endif