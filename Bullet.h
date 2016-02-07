//
// Created by rcastill on 2/6/16.
//

#ifndef PROJECT_STRAT_BULLET_H
#define PROJECT_STRAT_BULLET_H

#include "GraphicObject.h"

class GameScene;

class Bullet : public GraphicObject
{
public:
    Bullet(GameScene *gameScene, float x, float y, double angle);

    void init();
    void continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState);
    void render(Renderer &renderer);

private:
    GameScene *gameScene;
    Texture *asset;
    Position pos;
};


#endif //PROJECT_STRAT_BULLET_H
