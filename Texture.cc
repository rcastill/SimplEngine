//
// Created by rcastill on 12/25/15.
//

#include "Texture.h"

Texture::Texture(string path) :
    Resource(path),
    sdlTexture(nullptr),
    fullSource(true)
{
}

Texture::~Texture()
{
    if (sdlTexture)
        SDL_DestroyTexture(sdlTexture);
}

void Texture::updateInfo()
{
    SDL_QueryTexture(sdlTexture, &format, &access, &width, &height);
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
