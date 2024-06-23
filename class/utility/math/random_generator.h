#ifndef _RANDOM_GENERATOR
#define _RANDOM_GENERATOR

#include <iostream>
#include <cmath>
#include "./vector2.h"

namespace Random {
    // generate a random float in [min, max[
    float get_float(float min = 0, float max = 1);
    // generate a random int in [min, max[
    int get_int(int min, int max);
    // generate a random vector in [min, max[
    Vector2 get_vect2(Vector2 min = Vector2(), Vector2 max = Vector2(1, 1));
    // generate a random vector in the disk of radius <radius> centered on <center>
    Vector2 get_vect2_in_circle(Vector2 center = Vector2(), float radius = 1);
    // return true or false from proba (0 returns always false)
    bool get_bool(float proba = 0.5);
}

#endif