#ifndef VECTOR2D_H
#define VECTOR2D_H
struct Vector2D {
    float x, y;
    Vector2D(float X, float Y) : x(X), y(Y) {}
    float getX() const { return x; }
    float getY() const { return y; }
};
#endif