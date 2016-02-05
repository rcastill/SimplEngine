//
// Created by rcastill on 1/25/16.
//

#ifndef PROJECT_STRAT_RENDERER_H
#define PROJECT_STRAT_RENDERER_H

#include <utility>
#include <SDL_render.h>
#include "Texture.h"
#include "Position.h"

class Renderer
{
public:
    Renderer(SDL_Renderer* renderer);
    Renderer();
    ~Renderer();

    Renderer& operator=(Renderer&& other);

    friend void swap(Renderer& first, Renderer& second);

    void renderTexture(Texture *texture, SDL_Rect dstrect, double angle = 0);
    void renderTexture(Texture *texture, int x, int y, int w, int h, double angle = 0);
    void renderTexture(Texture *texture, int x, int y, double angle = 0);
    void renderTexture(Texture *texture, Position vector3);

    void renderPresent();
    void renderClear();

    void enabled(bool renderEnabled);
    bool enabled() const;

private:
    SDL_Renderer *sdlRenderer;
    bool renderEnabled;
};


#endif //PROJECT_STRAT_RENDERER_H
