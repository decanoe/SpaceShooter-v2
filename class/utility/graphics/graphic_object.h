#ifndef _GRAPHIC_OBJECT_CLASS
#define _GRAPHIC_OBJECT_CLASS

#include "./screen.h"

class GraphicObject
{
public:
    virtual void update(const Screen& screen) const;
};

#endif