//
// Created by rcastill on 1/24/16.
//

#include "GameScene.h"

GameScene::GameScene(Game *game) :
    game(game),
    stick(nullptr),
    stickEnabled(true)
{

}

void GameScene::init()
{
    stick = addChild<TestObject>();
    backButton = addChild<SimpleButton>(this, "Back");

    enabled(false);
}

void GameScene::update(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
        stickEnabled = !stickEnabled;
        stick->enabled(stickEnabled);
    }
}

void GameScene::onPrimaryClick(SimpleButton *button)
{
    if (button == backButton)
        game->toMainMenu();
}
