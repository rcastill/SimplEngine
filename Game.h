//
// Created by rcastill on 12/27/15.
//

#ifndef PROJECT_STRAT_GAME_H
#define PROJECT_STRAT_GAME_H

#include "GraphicObject.h"
#include "MainMenu.h"
#include "TestObject.h"
#include "GameScene.h"
#include <string>
#include <sstream>

class MainMenu;
class GameScene;

using namespace std;

class Game : public GraphicObject
{
    enum State
    {
        IN_MAIN_MENU,
        IN_GAME
    };

public:
    Game(string baseTitle);
    ~Game();

    void init();
    void onQuit();
    void onKeyPressed(SDL_Keycode key);
    void startGame();

    void toMainMenu();

private:
    MainMenu *mainMenu;
    GameScene *gameScene;
    State currentState;
    string baseTitle;
};


#endif //PROJECT_STRAT_GAME_H
