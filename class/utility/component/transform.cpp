#ifndef _TRANSFORM_CLASS

#include "./transform.h"

unsigned int Transform::ID_COUNT = 0;
Transform::Transform(std::string name, Transform* parent) {
    this->ID = ID_COUNT++;
    this->name = name;
    this->parent = parent;
};
std::string Transform::to_str() const { return "Transform(name: \"" + this->name + "\", \tID: " + std::to_string(this->ID) + ")"; };

void Transform::update() {
    for (Component* c : this->components)
    {
        c->update();
    }
}

Vector2 Transform::root_position() {
    if (this->parent == nullptr) return this->local_position;
    return this->parent->root_position();
}
Vector2 Transform::global_position() {
    if (this->parent == nullptr) return this->local_position;
    return this->local_position.rotate(this->parent->global_angle()) + this->parent->global_position();
}
float Transform::global_angle() {
    if (this->parent == nullptr) return this->local_angle;
    return this->local_angle + this->parent->local_angle;
}
Vector2 Transform::global_size() {
    if (this->parent == nullptr) return this->local_size;
    return this->local_size * this->parent->local_size;
}

void Transform::set_global_pos(Vector2 position) {
    if (this->parent == nullptr) this->local_position = position;
    else this->local_position = (position - this->parent->global_position()).rotate(-this->parent->global_angle());
}
void Transform::set_global_angle(float angle) {
    if (this->parent == nullptr) this->local_angle = angle;
    else this->local_angle = angle - parent->global_angle();
}

void Transform::release() {
    for (Component* c: this->components)
    {
        c->release();
        delete c;
    }
}
#endif