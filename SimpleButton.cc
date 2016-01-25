//
// Created by rcastill on 1/23/16.
//

#include "SimpleButton.h"
#include "GraphicsEngine.h"

#include <iostream>

SimpleButton::SimpleButton(ButtonMaster *master, string text) :
    master(master),
    text(text),
    x(100),
    y(100)
{
    cout << "SimpleButton()" << endl;
}

SimpleButton::~SimpleButton()
{
    cout << "~SimpleButton()" << endl;
}

void SimpleButton::init()
{
    cantarellRegular = gfx->loadFont("Cantarell-Regular.ttf", 24);
    normalTexture = gfx->makeText(cantarellRegular, text, Color::WHITE, FQ_MID);
    hoverTexture = gfx->makeText(cantarellRegular, text, Color::BLACK, FQ_MID);
    activeTexture = normalTexture;
}

void SimpleButton::update(SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION) {
        if (inside(event.motion.x, event.motion.y))
            activeTexture = hoverTexture;
        else
            activeTexture = normalTexture;
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (inside(event.button.x, event.button.y))
            master->onPrimaryClick(this);
    }
}

void SimpleButton::render()
{
    gfx->renderTexture(activeTexture, x, y);
}

bool SimpleButton::inside(int x, int y)
{
    return (x >= this->x && x <= this->x + activeTexture->getWidth() &&
            y >= this->y && y <= this->y + activeTexture->getHeight());
}
