//
// Created by rcastill on 12/27/15.
//

#include "Game.h"

#include <iostream>

Game::Game() :
    currentState(IN_MAIN_MENU)
{
    cout << "Game()" << endl;
}

Game::~Game()
{
    cout << "~Game()" << endl;
}

void Game::init()
{
    mainMenu = addChild<MainMenu>(this);
    gameScene = addChild<GameScene>(this);
}

void Game::update(SDL_Event &event)
{
    if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        gfx->stop();
}

void Game::startGame()
{
    mainMenu->enabled(false);
    gameScene->enabled(true);
}

void Game::toMainMenu()
{
    mainMenu->enabled(true);
    gameScene->enabled(false);
}
