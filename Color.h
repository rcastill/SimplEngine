//
// Created by rcastill on 12/18/15.
//

#ifndef PROJECT_STRAT_COLOR_H
#define PROJECT_STRAT_COLOR_H

#include <SDL2/SDL_stdinc.h>
#include <SDL_pixels.h>

class Color
{
public:
    Color(int r, int g, int b, int a = 255);

    Uint8 r() const;
    Uint8 g() const;
    Uint8 b() const;
    Uint8 a() const;

    void r(int r);
    void g(int g);
    void b(int b);
    void a(int a);

    void rgb(int r, int g, int b);
    void rgba(int r, int g, int b, int a);

    SDL_Color getSdlColor();

    Color negative();

    static Color BLACK;
    static Color WHITE;
    static Color RED;

private:

    SDL_Color sdlColor;
    int red;
    int green;
    int blue;
    int alpha;
};

#endif //PROJECT_STRAT_COLOR_H
