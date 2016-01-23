//
// Created by rcastill on 12/27/15.
//

#include "Game.h"

void Game::init()
{
    stick = gfx->addObject<TestObject>();
}

void Game::update(SDL_Event &event)
{
    if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        gfx->stop();
}
