#include <iostream>
#include <math.h>
#include "Vec2.h"

Vec2 make_vec2(double x, double y)
{
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

Vec2 operator+(Vec2 a, Vec2 b)
{
    Vec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

Vec2 operator-(Vec2 a, Vec2 b)
{
    Vec2 r;
    r.x = a.x - b.x;

    r.y = a.y - b.y;
    return r;
}

Vec2 operator+=(Vec2 a, Vec2 b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vec2 operator*(float a, Vec2 b)
{
    Vec2 r;
    r.x = a * b.x;
    r.y = a * b.y;
    return r;
}

Vec2 operator*(Vec2 b, float a)
{
    Vec2 r;
    r.x = a * b.x;
    r.y = a * b.y;
    return r;
}

Vec2 operator/(Vec2 a, float b)
{
    Vec2 r;
    r.x = a.x / b;
    r.y = a.y / b;
    return r;
}

double distance(Vec2 a, Vec2 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}