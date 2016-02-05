//
// Created by rcastill on 12/25/15.
//

#ifndef PROJECT_STRAT_TEXTURE_H
#define PROJECT_STRAT_TEXTURE_H

#include <SDL2/SDL_render.h>
#include <string>
#include "Resource.h"
#include <memory>
#include <functional>

using namespace std;

class Texture : public Resource
{
public:
    Texture(string path);
    ~Texture();

    void updateInfo();

    int getWidth();
    int getHeight();
    void getSize(int &w, int &h);

private:
    friend class GraphicsEngine;
    friend class Renderer;

    SDL_Texture *sdlTexture;
    SDL_Rect srcrect;
    bool fullSource;

    Uint32 format;
    int access;
    int width;
    int height;
};


#endif //PROJECT_STRAT_TEXTURE_H
