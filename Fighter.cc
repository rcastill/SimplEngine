//
// Created by rcastill on 1/31/16.
//

#include "Fighter.h"
#include "GameScene.h"

#include <iostream>

Fighter::Fighter(GameScene *gameScene, string usernameText) :
    gameScene(gameScene),
    follow(false),
    pos(400, 400),
    usernameText(usernameText)
{
    pos.speed = 5;
}

void Fighter::init()
{
    asset = loadTexture("spaceship.png");
    renderLayer(LEVEL1);

    cantarellRegular = loadFont("Cantarell-Regular.ttf", 16);
    usernameTexture = makeText(cantarellRegular, usernameText, Color::WHITE, FQ_MID);
}

void Fighter::continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState)
{
    pos.lookTowards(mouseState.pos.x, mouseState.pos.y);
    angleTexture = makeText(cantarellRegular, to_string((int)pos.r) + " deg", Color::WHITE, FQ_MID, false);

    if (follow)
        pos.moveTowards(mouseState.pos.x, mouseState.pos.y, deltaTime());
}

void Fighter::render(Renderer &renderer)
{
    renderer.renderTexture(usernameTexture, (int) pos.x, (int) (pos.y - 80));
    renderer.renderTexture(angleTexture, (int) pos.x, (int) (pos.y + 80));
    renderer.renderTexture(asset, pos);
}

void Fighter::onMouseLeftReleased(int x, int y)
{
    gameScene->addChild<Bullet>(gameScene, pos.x, pos.y, pos.r);
}

void Fighter::onKeyReleased(SDL_Keycode key)
{
    if (key == SDLK_SPACE)
        follow = !follow;
}
