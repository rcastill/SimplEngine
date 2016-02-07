//
// Created by rcastill on 2/6/16.
//

#include <iostream>
#include "Bullet.h"

Bullet::Bullet(GameScene *gameScene, float x, float y, double angle) :
    gameScene(gameScene),
    pos(x, y, angle)
{
    pos.speed = 300;
}

void Bullet::init()
{
    asset = loadTexture("bullet.png");
}

void Bullet::continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState)
{
    /* temporary */
    if (pos.x > screenWidth() || pos.y < 0 || pos.x < 0 || pos.y > screenHeight())
        enabled(false);

    pos.moveForward(deltaTime());
}

void Bullet::render(Renderer &renderer)
{
    renderer.renderTexture(asset, pos);
}
