#ifndef _RIGID_OBJECT_CLASS

#include "./rigid_object.h"

RigidObject::RigidObject(Transform* transform, Collider* collider, float mass) {
    this->transform = transform;
    this->collider = collider;
    this->mass = mass;
}

void RigidObject::update() {
    this->transform->position += this->velocity * World::deltatime;
    this->velocity /= 1 + World::deltatime;

    this->transform->angle += this->angle_velocity * World::deltatime;
    this->angle_velocity /= 1 + World::deltatime;
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