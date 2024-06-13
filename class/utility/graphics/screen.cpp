#ifndef _SCREEN_CLASS

#include "./screen.h"

Screen::Screen(bool fullscreen, unsigned int width, unsigned int height)
{
    // init sdl if it was not
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL cannot be initialed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    this->window = SDL_CreateWindow(
        "SpaceShooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | (fullscreen? SDL_WINDOW_FULLSCREEN_DESKTOP : 0)
    );

    SDL_GetWindowSizeInPixels(window, &this->width, &this->height);
    std::cout << "w: " << this->width << " \th: " << this->height << "\n";

    if (window == NULL) {
        std::cerr << "SDL cannot create window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Screen::close() {
    //Destroy window  
    SDL_DestroyWindow(this->window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Window* Screen::get_window() {
    return this->window;
}

void Screen::render() {
}
void Screen::update() {
    SDL_GL_SwapWindow(this->window);
}

#endif