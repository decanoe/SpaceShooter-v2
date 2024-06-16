#ifndef _TRANSFORM_CLASS
#define _TRANSFORM_CLASS

#include "../math/vector2.h"

class Transform
{
private:
    static unsigned int ID_COUNT;
public:
    std::string name = "unnamed transform n";
    Vector2 position = Vector2();
    float angle = 0;
    Vector2 size = Vector2(1, 1);

    Transform();
    ~Transform() {}

    std::string to_str() const;
};

#endif