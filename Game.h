//
// Created by rcastill on 12/27/15.
//

#ifndef PROJECT_STRAT_GAME_H
#define PROJECT_STRAT_GAME_H

#include "GraphicObject.h"
#include "MainMenu.h"
#include "TestObject.h"
#include "GameScene.h"

class MainMenu;
class GameScene;

class Game : public GraphicObject
{
    enum State
    {
        IN_MAIN_MENU,
        IN_GAME
    };

public:
    Game();
    ~Game();

    void init();
    void update(SDL_Event &event);

    void startGame();

    void toMainMenu();

private:
    MainMenu *mainMenu;
    GameScene *gameScene;
    State currentState;
};


#endif //PROJECT_STRAT_GAME_H
