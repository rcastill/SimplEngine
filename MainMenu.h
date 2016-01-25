//
// Created by rcastill on 1/23/16.
//

#ifndef PROJECT_STRAT_MAINMENU_H
#define PROJECT_STRAT_MAINMENU_H

#include "GfxSDL2Engine.h"
#include "Game.h"
#include "TestObject.h"
#include "SimpleButton.h"
#include "ButtonMaster.h"

class Game;

class MainMenu : public GraphicObject, public ButtonMaster
{
public:
    MainMenu(Game *game);
    ~MainMenu();

    void init();
    void update(SDL_Event &event);

    void onPrimaryClick(SimpleButton *button);

private:
    Game *game;

    SimpleButton *startButton;
    SimpleButton *exitButton;
};


#endif //PROJECT_STRAT_MAINMENU_H
