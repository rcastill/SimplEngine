//
// Created by rcastill on 1/31/16.
//

#ifndef PROJECT_STRAT_FIGHTER_H
#define PROJECT_STRAT_FIGHTER_H

#include "GraphicObject.h"
#include "Position.h"

class GameScene;

class Fighter : public GraphicObject
{
public:
    Fighter(GameScene *gameScene);

    void init();
    void continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState);
    void render(Renderer &renderer);

private:
    GameScene *gameScene;
    Texture *asset;

    Position pos;
};


#endif //PROJECT_STRAT_FIGHTER_H
