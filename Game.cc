//
// Created by rcastill on 12/27/15.
//

#include "Game.h"

#include <iostream>

Game::Game(string baseTitle) :
    currentState(IN_MAIN_MENU),
    baseTitle(baseTitle)
{
    cout << "Game()" << endl;
}

Game::~Game()
{
    cout << "~Game()" << endl;
}

void Game::init()
{
    windowTitle(baseTitle);
    mainMenu = addChild<MainMenu>(this);
    gameScene = addChild<GameScene>(this);
}

void Game::onQuit()
{
    stop();
}

void Game::onKeyPressed(SDL_Keycode key)
{
    if (key == SDLK_ESCAPE)
        stop();
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