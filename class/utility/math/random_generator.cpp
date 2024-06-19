#ifndef _RANDOM_GENERATOR

#include "./random_generator.h"

// generate a random float in [min, max[
float Random::get_float(float min, float max) {
    return min + (float)std::rand() / (float)RAND_MAX * (max - min);
}
// generate a random int in [min, max[
int Random::get_int(int min, int max) {
    return floorf(Random::get_float(min, max));
}
// generate a random vector in [min, max[
Vector2 Random::get_vect2(Vector2 min, Vector2 max) {
    return Vector2(Random::get_float(min.x, max.x), Random::get_float(min.y, max.y));
}
// generate a random vector in the disk or radius <radius> centered on <center>
Vector2 Random::get_vect2_in_circle(Vector2 center, float radius) {
    return center + Vector2::from_angle(Random::get_float(0, 2*PI)) * radius * std::sqrt(Random::get_float());
}
// return true or false from proba (0 returns always false)
bool Random::get_bool(float proba) {
    return ((float)std::rand() / (float)RAND_MAX) < proba;
}

#endif