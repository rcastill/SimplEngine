//
// Created by rcastill on 1/24/16.
//

#ifndef PROJECT_STRAT_GAMESCENE_H
#define PROJECT_STRAT_GAMESCENE_H


#include "GraphicObject.h"
#include "TestObject.h"
#include "SimpleButton.h"
#include "Game.h"

class Game;

class GameScene : public GraphicObject, public ButtonMaster
{
public:
    GameScene(Game *game);

    void init();
    void update(SDL_Event &event);

    void onPrimaryClick(SimpleButton *button);

private:
    Game *game;

    TestObject *stick;
    bool stickEnabled;

    SimpleButton *backButton;
};


#endif //PROJECT_STRAT_GAMESCENE_H
