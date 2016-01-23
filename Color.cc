//
// Created by rcastill on 12/18/15.
//

#include "Color.h"

Color::Color(int r, int g, int b, int a)
{
    rgba(r, g, b, a);
}

Uint8 Color::r() const
{
    return (Uint8) red;
}

Uint8 Color::g() const
{
    return (Uint8) green;
}

Uint8 Color::b() const
{
    return (Uint8) blue;
}

Uint8 Color::a() const
{
    return (Uint8) alpha;
}

void Color::r(int r)
{
    red = r % 256;
}

void Color::g(int g)
{
    green = g % 256;
}

void Color::b(int b)
{
    blue = b % 256;
}

void Color::a(int a)
{
    alpha = a % 256;
}

void Color::rgb(int r, int g, int b)
{
    this->r(r);
    this->g(g);
    this->b(b);
}

void Color::rgba(int r, int g, int b, int a)
{
    rgb(r, g, b);
    this->a(a);
}

Color Color::negative()
{
    return Color(255 - red, 255 - green, 255 - blue, alpha);
}

Color Color::BLACK(0, 0, 0);
Color Color::WHITE(255, 255, 255);