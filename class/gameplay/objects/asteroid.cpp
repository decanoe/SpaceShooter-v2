#ifndef _ASTEROID_CLASS

#include "./asteroid.h"
#include "../../utility/math/random_generator.h"

Asteroid::Asteroid() {
    int sprite_index = std::rand() % 5;
    this->name = "Asteroid " + std::to_string(sprite_index);
    this->angle = Random::get_float(0, 2*PI);
    float scale = Random::get_float(0.5, 5);

    Sprite sprite = Sprite::copy(Graphics::sprite_sheet, Vector2Int((13 + sprite_index) * 32, 32), Vector2Int(32, 32), Vector2Int(64, 64) * scale);
    sprite.name = "Asteroid " + std::to_string(sprite_index);
    this->sprite_renderer = SpriteRenderer(this, sprite);
    
    this->rect_collider = RectCollider(this, Rect(sprite.get_size()).recenter());

    this->rigid_object = RigidObject(this, &this->rect_collider, 500 * scale * scale);
    this->rigid_object.set_angle_velocity(Random::get_float(-1, 1) * PI * 0.1);
}
void Asteroid::release() {
    this->sprite_renderer.release();
}
void Asteroid::update() {
    this->rigid_object.update();
}
void Asteroid::insert_to_world(bool free_object) {
    this->free_object = free_object;
    World::add_updatable(this, this->position);
    World::add_object_renderer(&this->sprite_renderer, this->position);
    World::add_object_renderer(&this->rect_collider, this->position);
}
void Asteroid::change_chunk(Vector2Int previous_chunk_index) {
    World::remove_updatable(this, previous_chunk_index);
    World::remove_object_renderer(&this->sprite_renderer, previous_chunk_index);
    World::remove_object_renderer(&this->rect_collider, previous_chunk_index);

    this->insert_to_world(this->free_object);
}

#endif