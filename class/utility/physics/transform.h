#ifndef _TRANSFORM_CLASS
#define _TRANSFORM_CLASS

#include "../math/vector2.h"

class Transform
{
public:
    Vector2 position;
    float angle;
    Vector2 size;
    Transform();
    ~Transform();
};


#endif