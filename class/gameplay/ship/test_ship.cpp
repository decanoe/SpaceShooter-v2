#ifndef _TEST_SHIP_CLASS

#include "./test_ship.h"

#define lerp(a, b, t) (a) + ((b) - (a)) * (t)
#define inv_lerp(a, b, x) __max(__min(((x) - (a)) / ((b) - (a)), 1), 0)

#define MASS 500
#define SPEED (512 * MASS)

TestShip::TestShip(Vector2 position) {
    this->position = position;
    this->name = "test ship";

    this->rect_collider = RectCollider(this, Rect(64, 64).recenter());
    this->rigid_object = RigidObject(this, &this->rect_collider, MASS);

    Sprite sprite = Sprite::copy(Graphics::sprite_sheet, Vector2Int(0, 32), Vector2Int(32, 32), Vector2Int(64, 64));
    sprite.name = "ship sprite";
    this->sprite_renderer = SpriteRenderer(this, sprite);
    this->sprite_renderer.z_index = 100;
}
void TestShip::release() {
    this->sprite_renderer.release();
}
void TestShip::update() {
    this->rigid_object.update();
    this->rigid_object.set_velocity(this->rigid_object.get_velocity() / (1 + World::deltatime));
    this->rigid_object.set_angle_velocity(this->rigid_object.get_angle_velocity() / (1 + World::deltatime));
}
void TestShip::insert_to_world(bool free_object) {
    this->free_object = free_object;
    World::add_updatable(this, this->position);
    World::add_object_renderer(&this->sprite_renderer, this->position);
    World::add_object_renderer(&this->rect_collider, this->position);
}
void TestShip::change_chunk(Vector2Int previous_chunk_index) {
    World::remove_updatable(this, previous_chunk_index);
    World::remove_object_renderer(&this->sprite_renderer, previous_chunk_index);
    World::remove_object_renderer(&this->rect_collider, previous_chunk_index);

    this->insert_to_world(this->free_object);
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