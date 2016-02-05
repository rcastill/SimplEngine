//
// Created by rcastill on 1/31/16.
//

#include "Fighter.h"
#include "GraphicObject.h"

Fighter::Fighter(GameScene *gameScene) :
    gameScene(gameScene),
    pos(400, 400, 5)
{
}

void Fighter::init()
{
    asset = loadTexture("fighter.png");
}

void Fighter::continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState)
{
    pos.lookTowards(mouseState.pos.x, mouseState.pos.y);
    pos.moveTowards(mouseState.pos.x, mouseState.pos.y, deltaTime());
}

void Fighter::render(Renderer &renderer)
{
    renderer.renderTexture(asset, pos);
}
