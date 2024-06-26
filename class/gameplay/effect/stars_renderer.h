#ifndef _STARS_RENDERER_CLASS
#define _STARS_RENDERER_CLASS

#include "SDL.h"
#include "../../utility/graphics/object_renderer.h"
#include "../general/graphics.h"

class StarsRenderer: public ObjectRenderer
{
protected:
    Vector2* positions = nullptr;
    float* distances = nullptr;
    bool* thick = nullptr;
    int count = 0;
public:
    StarsRenderer(int count);
    void draw() const override;
    void release() override;
    std::string to_str() const override;
};

#endif