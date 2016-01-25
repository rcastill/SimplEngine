//
// Created by rcastill on 1/23/16.
//

#ifndef PROJECT_STRAT_FONT_H
#define PROJECT_STRAT_FONT_H

#include <SDL2/SDL_ttf.h>
#include "Resource.h"
#include <string>

using namespace std;

class Font : public Resource
{
public:
    operator bool();

private:
    friend class GraphicsEngine;

    Font(string path, int fontSize);

    int fontSize;
    unique_ptr<TTF_Font, function<void(TTF_Font*)>> ttfFont;
};


#endif //PROJECT_STRAT_FONT_H
