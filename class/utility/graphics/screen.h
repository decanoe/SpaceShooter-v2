#ifndef _SCREEN_CLASS
#define _SCREEN_CLASS

#include "../math/vector3.h"

#include "SDL.h"


class Screen
{
private:
    SDL_Window *window = NULL;
    SDL_GLContext context = nullptr;
public:
    int width = 1080;
    int height = 768;

    Screen(bool fullscreen, unsigned int width = 1080, unsigned int height = 768);
    void close();

    SDL_Window* get_window();

    void render();
    void update();
};

#endif