#include <iostream>
#define SDL_MAIN_HANDLED
#include <chrono>
#include "class/utility/graphics/screen.h"

int main(int argc, char *args[]) {
    Screen screen = Screen(true);

    bool loop = true;
    float deltatime = 0.001;
    while (loop) {
        auto start = std::chrono::system_clock::now();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type)
            {
            case SDL_QUIT:
                loop = false;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                }
                break;
            }
        }
        
        screen.render();
        screen.update();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_time = end-start;
        double elapsed_seconds = elapsed_time.count();
        deltatime = elapsed_seconds;
    }

    screen.close();

    SDL_Quit();
    return 0;
}