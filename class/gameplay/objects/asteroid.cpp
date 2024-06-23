#ifndef _ASTEROID_CLASS

#include "./asteroid.h"
#include "../../utility/math/random_generator.h"

Asteroid::Asteroid(Transform* parent): Transform("asteroid", parent) {
    int sprite_index = std::rand() % 5;
    this->name = "Asteroid " + std::to_string(sprite_index);
    this->local_angle = Random::get_float(0, 2*PI);
    float scale = Random::get_float(0.5, 5);

    Sprite sprite = Sprite::copy(Graphics::sprite_sheet, Vector2Int((13 + sprite_index) * 32, 32), Vector2Int(32, 32), Vector2Int(64, 64) * scale);
    sprite.name = "Asteroid " + std::to_string(sprite_index);
    SpriteRenderer* sprite_renderer = new SpriteRenderer(this, sprite);
    
    RectCollider* rect_collider = new RectCollider(this, Rect(sprite.get_size()).recenter());

    RigidObject* rigid_object = new RigidObject(this, 500 * scale * scale, Physics::PhysicsLayer::Terrain);
    rigid_object->set_angle_velocity(Random::get_float(-1, 1) * PI * 0.1);

    this->components.push_back(sprite_renderer);
    this->components.push_back(rect_collider);
    this->components.push_back(rigid_object);
}
#endif