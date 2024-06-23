#ifndef _RIGID_OBJECT_CLASS

#include "./rigid_object.h"

bool Physics::do_collide(PhysicsLayer a, PhysicsLayer b) {
    switch (a)
    {
    case Physics::PhysicsLayer::Garbage:
        switch (b)
        {
            case Physics::PhysicsLayer::Garbage: return false;
            case Physics::PhysicsLayer::Terrain: return false;
        }
        break;
    case Physics::PhysicsLayer::Terrain:
        switch (b)
        {
            case Physics::PhysicsLayer::Garbage: return false;
            case Physics::PhysicsLayer::Terrain: return false;
        }
        break;
    }

    return true;
}

RigidObject::RigidObject(Transform* transform, float mass, Physics::PhysicsLayer layer): Component(transform) {
    this->layer = layer;
    this->mass = mass;
}

void RigidObject::update() {
    this->transform->set_global_pos(this->transform->global_position() + this->velocity * World::deltatime);
    this->transform->local_angle += this->angle_velocity * World::deltatime;
}

void RigidObject::add_force(Vector2 force) {
    this->velocity += force / this->mass;
}
void RigidObject::add_rotation(float force) {
    this->angle_velocity += force;
}

void RigidObject::set_velocity(Vector2 velocity) {
    this->velocity = velocity;
}
Vector2 RigidObject::get_velocity() const {
    return this->velocity;
}
void RigidObject::set_angle_velocity(float angle_velocity) {
    this->angle_velocity = angle_velocity;
}
float RigidObject::get_angle_velocity() const {
    return this->angle_velocity;
}
void RigidObject::set_mass(float mass) {
    this->mass = mass;
}
float RigidObject::get_mass() const {
    return this->mass;
}

std::string RigidObject::to_str() const {
    return "RigidObject(transform: \"" + this->transform->name + "\",\t mass: " + std::to_string(this->mass) + ",\t velocity: " + this->velocity.to_str() + ",\t angle_velocity: " + std::to_string(this->angle_velocity) + ")";
};
#endif