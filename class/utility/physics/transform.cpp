#ifndef _TRANSFORM_CLASS

#include "./transform.h"

Transform::Transform() { this->name += ID_COUNT++; };
unsigned int Transform::ID_COUNT = 0;
std::string Transform::to_str() const { return "Transform(name: \"" + this->name + "\")"; };

#endif