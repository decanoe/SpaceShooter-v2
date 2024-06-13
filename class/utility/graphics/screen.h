#ifndef _SCREEN_CLASS
#define _SCREEN_CLASS

#include <iostream>
#include "SDL.h"

class Screen
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
public:
    int width = 1080;
    int height = 768;

    Screen(bool fullscreen, unsigned int width = 1080, unsigned int height = 768);
    void close();

    SDL_Window* get_window() const;
    SDL_Renderer* get_renderer() const;

    void update();
};

#endif