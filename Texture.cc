//
// Created by rcastill on 12/25/15.
//

#include "Texture.h"

Texture::Texture(string path) :
    Resource(path),
    fullSource(true)
{
    sdlTexture.get_deleter() = [](SDL_Texture *t) { SDL_DestroyTexture(t); };
}

void Texture::updateInfo()
{
    SDL_QueryTexture(sdlTexture.get(), &format, &access, &width, &height);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::getSize(int &w, int &h)
{
    w = width;
    h = height;
}
