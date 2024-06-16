#ifndef _RIGID_OBJECT_CLASS
#define _RIGID_OBJECT_CLASS

#include "../math/vector2.h"
#include "./transform.h"
#include "./collider.h"
#include "../updatable.h"

class RigidObject: public Updatable
{
protected:
    Transform* transform = nullptr;
    Collider* collider = nullptr;
    Vector2 velocity = Vector2();
    float mass = 500;
    float angle_velocity = 0;
public:
    RigidObject(Transform* transform, Collider* collider, float mass = 500);
    RigidObject() {}
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