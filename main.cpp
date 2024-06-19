#include <iostream>
#define SDL_MAIN_HANDLED
#include <chrono>

#include "class/gameplay/ship/test_ship.h"
#include "class/gameplay/general/graphics.h"
#include "class/gameplay/general/world.h"

int main(int argc, char *args[]) {
    World::world_setup();

    TestShip* ship = new TestShip(Vector2());
    World::world_center = ship;
    ship->insert_to_world(true);

    bool loop = true;
    float deltatime = 0.001;
    while (loop) {
        auto start = std::chrono::system_clock::now();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ship->manage_event(e);

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
                    case SDLK_b:
                        if (World::debug & DEBUG_COLLIDER) World::debug -= DEBUG_COLLIDER;
                        else World::debug &= DEBUG_COLLIDER;
                        break;
                }
                break;
            }
        }
        ship->manage_continuous_event();
        
        World::update(deltatime);
        World::render();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_time = end-start;
        double elapsed_seconds = elapsed_time.count();
        deltatime = elapsed_seconds;

        std::cout << "fps: " << (1/deltatime) << "                            \r";
    }

    World::release();
    Graphics::sprite_sheet.release();
    Graphics::screen.close();

    SDL_Quit();
    return 0;
}