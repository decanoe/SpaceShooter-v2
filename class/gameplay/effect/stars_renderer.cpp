#ifndef _STARS_RENDERER_CLASS

#include "./stars_renderer.h"
#include "../../utility/math/rect.h"
#include "../../utility/math/random_generator.h"

StarsRenderer::StarsRenderer(int count): ObjectRenderer(nullptr) {
    this->z_index = -1024;
    this->count = count;
    this->positions = new Vector2[this->count];
    this->distances = new float[this->count];
    this->thick = new bool[this->count];

    for (int i = 0; i < this->count; i++)
    {
        float v = Random::get_float();
        this->distances[i] = 0.1 + (1 - v * v) * 0.9;

        this->positions[i] = Random::get_vect2(Vector2(), Vector2(Graphics::screen.width, Graphics::screen.height));
        
        this->thick[i] = Random::get_bool(0.25);
    }
    
}
void StarsRenderer::draw() const {
    for (int i = 0; i < this->count; i++)
    {
        Vector2 pos = this->positions[i] - World::get_world_center() * this->distances[i];
        pos.x -= floorf(pos.x / Graphics::screen.width) * Graphics::screen.width;
        pos.y -= floorf(pos.y / Graphics::screen.height) * Graphics::screen.height;

        int r = 200 * (1 - this->distances[i]*this->distances[i]*this->distances[i]);
        int g = 55 + 150 * this->distances[i];
        int b = 55 + 150 * this->distances[i] * this->distances[i];

        SDL_SetRenderDrawColor(Graphics::screen.get_renderer(), r, g, b, SDL_ALPHA_OPAQUE);

        if (this->thick[i]) {
            SDL_RenderDrawLineF(Graphics::screen.get_renderer(), pos.x - 1, pos.y, pos.x + 1, pos.y);
            SDL_RenderDrawLineF(Graphics::screen.get_renderer(), pos.x, pos.y - 1, pos.x, pos.y + 1);
        }
        else SDL_RenderDrawPointF(Graphics::screen.get_renderer(), pos.x, pos.y);
    }
}
void StarsRenderer::release() {
    if (this->positions != nullptr) delete this->positions;
    if (this->distances != nullptr) delete this->distances;

    this->positions = nullptr;
    this->distances = nullptr;
    this->count = 0;
}
std::string StarsRenderer::to_str() const {
    return "STARS(nb: " + std::to_string(this->count) + ")";
}

#endif