#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Vector2D.h"
struct Transform {
    Vector2D position;
    Transform(float x, float y) : position(x,y) {}
    Vector2D& getPosition() { return position; }
};
#endif