#ifndef _TRANSFORM_CLASS

#include "./transform.h"

unsigned int Transform::ID_COUNT = 0;
Transform::Transform() { this->name += std::to_string(ID_COUNT++); };
std::string Transform::to_str() const { return "Transform(name: \"" + this->name + "\")"; };

#endif