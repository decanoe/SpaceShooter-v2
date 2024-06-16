#ifndef _TEST_SHIP_CLASS

#include "./test_ship.h"

#define lerp(a, b, t) (a) + ((b) - (a)) * (t)
#define inv_lerp(a, b, x) __max(__min(((x) - (a)) / ((b) - (a)), 1), 0)

#define MASS 500
#define SPEED (256 * MASS)

TestShip::TestShip(Vector2 position) {
    this->position = position;

    this->rect_collider = RectCollider(this, Rect(32, 32).recenter());
    this->rigid_object = RigidObject(this, &this->rect_collider, MASS);

    Sprite sprite = Sprite::copy(Graphics::sprite_sheet, Vector2Int(0, 32), Vector2Int(32, 32));
    sprite.name = "ship sprite";
    this->sprite_renderer = SpriteRenderer(this, sprite);
}
void TestShip::release() {
    this->sprite_renderer.release();
}
void TestShip::update() {
    this->rigid_object.update();
}

void TestShip::manage_event(const SDL_Event& event) {
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                break;
        }
        break;
    }
}
void TestShip::manage_continuous_event() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
        this->rigid_object.add_force(Vector2(-1, 0) * World::deltatime * SPEED);
    }
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        this->rigid_object.add_force(Vector2(1, 0) * World::deltatime * SPEED);
    }
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) {
        this->rigid_object.add_force(Vector2(0, -1) * World::deltatime * SPEED);
    }
    if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) {
        this->rigid_object.add_force(Vector2(0, 1) * World::deltatime * SPEED);
    }



    
    Vector2Int mouse_position;
    Uint32 button_state = SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

    if (button_state&SDL_BUTTON(1)) {
        this->rigid_object.add_force(Vector2(0, -1).rotate(-angle) * World::deltatime * SPEED);
    }

    float rotation_needed = ((Vector2)mouse_position - Graphics::world_to_screen(this->position)).signed_angle(Vector2::from_angle(this->angle + PI/2));
    this->rigid_object.set_angle_velocity(lerp(-PI, PI, inv_lerp(-0.5, 0.5, rotation_needed)));
}

#endif