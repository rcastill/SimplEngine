//
// Created by rcastill on 1/25/16.
//

#include "Renderer.h"

#include <iostream>

Renderer::Renderer(SDL_Renderer *renderer) :
    sdlRenderer(renderer),
    renderEnabled(false)
{
}

Renderer::Renderer() :
        Renderer(nullptr)
{
}

Renderer::~Renderer()
{
    if (sdlRenderer)
        SDL_DestroyRenderer(sdlRenderer);
}

Renderer &Renderer::operator=(Renderer &&other)
{
    swap(*this, other);
    return *this;
}

void Renderer::renderPresent()
{
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::renderClear()
{
    if (sdlRenderer)
        SDL_RenderClear(sdlRenderer);
}

void swap(Renderer &first, Renderer &second)
{
    using std::swap;
    swap(first.sdlRenderer, second.sdlRenderer);
}

void Renderer::enabled(bool renderEnabled)
{
    this->renderEnabled = renderEnabled;
}

bool Renderer::enabled() const
{
    return renderEnabled;
}

void Renderer::renderTexture(Texture *texture, SDL_Rect dstrect, double angle)
{
    if (!renderEnabled)
        return;

    if (!texture)
        throw runtime_error("Could not render texture.");

    dstrect.x = dstrect.x - dstrect.w / 2;
    dstrect.y = dstrect.y - dstrect.h / 2;

    SDL_RenderCopyEx(sdlRenderer,
                     texture->sdlTexture,
                     (texture->fullSource) ? 0 : &(texture->srcrect),
                     &dstrect,
                     angle,
                     NULL, // Rotation pivot: Center
                     SDL_FLIP_NONE);
}

void Renderer::renderTexture(Texture *texture, int x, int y, int w, int h, double angle)
{
    if (!renderEnabled)
        return;

    SDL_Rect dstrect = {x, y, w, h};
    renderTexture(texture, dstrect, angle);
}

void Renderer::renderTexture(Texture *texture, int x, int y, double angle)
{
    if (!renderEnabled)
        return;

    if (!texture)
        throw runtime_error("Could not render texture.");

    int w, h;
    texture->getSize(w, h);
    renderTexture(texture, x, y, w, h, angle);
}

void Renderer::renderTexture(Texture *texture, const Position &vector3)
{
    if (!renderEnabled)
        return;

    renderTexture(texture, (int) vector3.x, (int) vector3.y, vector3.r);
}
