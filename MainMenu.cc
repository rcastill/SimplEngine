//
// Created by rcastill on 1/23/16.
//

#include "MainMenu.h"

#include <iostream>

MainMenu::MainMenu(Game *game) :
    game(game)
{
    cout << "MainMenu()" << endl;
}

MainMenu::~MainMenu()
{
    cout << "~MainMenu()" << endl;
}

void MainMenu::init()
{
    startButton = addChild<SimpleButton>(this, "Start Game");
    exitButton = addChild<SimpleButton>(this, "Exit");
    exitButton->y += 50;
}

void MainMenu::update(SDL_Event &event)
{
}

void MainMenu::onPrimaryClick(SimpleButton *button)
{
    if (button == startButton)
        game->startGame();

    else if (button == exitButton)
        stop();
}
