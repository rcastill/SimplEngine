//
// Created by rcastill on 1/24/16.
//

#include "GameScene.h"

#include <iostream>

GameScene::GameScene(Game *game) :
    game(game)
{
}

void GameScene::init()
{
    background = loadTexture("background.png");
    fighter = addChild<Fighter>(this, "volkr");
    enabled(false);
    renderLayer(BACKGROUND);
}


void GameScene::render(Renderer &renderer)
{
    renderer.renderTexture(background, screenWidth() / 2, screenHeight() / 2);
}

void GameScene::onKeyReleased(SDL_Keycode key)
{
    if (key == SDLK_ESCAPE)
        game->toMainMenu();
}