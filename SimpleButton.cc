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
    cantarellRegular = loadFont("Cantarell-Regular.ttf", 24);
    normalTexture = makeText(cantarellRegular, text, Color::WHITE, FQ_MID);
    hoverTexture = makeText(cantarellRegular, text, Color::BLACK, FQ_MID);
    activeTexture = normalTexture;
}

void SimpleButton::onMouseMotion(int x, int y)
{
    if (inside(x, y))
        activeTexture = hoverTexture;
    else
        activeTexture = normalTexture;
}

void SimpleButton::onMouseLeftReleased(int x, int y)
{
    if (inside(x, y))
        master->onPrimaryClick(this);
}

void SimpleButton::render(Renderer &renderer)
{
    renderer.renderTexture(activeTexture, x, y);
}

bool SimpleButton::inside(int x, int y)
{
    return (x >= this->x - activeTexture->getWidth() / 2 && x <= this->x + activeTexture->getWidth() / 2 &&
            y >= this->y - activeTexture->getHeight() / 2 && y <= this->y + activeTexture->getHeight() / 2);
}
