//
// Created by rcastill on 1/24/16.
//

#ifndef PROJECT_STRAT_GAMESCENE_H
#define PROJECT_STRAT_GAMESCENE_H


#include "GraphicObject.h"
#include "SimpleButton.h"
#include "Game.h"
#include "Fighter.h"

class Game;

class GameScene : public GraphicObject
{
public:
    GameScene(Game *game);

    void init();
    void render(Renderer &renderer);

    void onKeyReleased(SDL_Keycode key);

private:
    Game *game;
    Fighter *fighter;
    Texture *background;
};


#endif //PROJECT_STRAT_GAMESCENE_H
