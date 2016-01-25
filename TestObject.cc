//
// Created by rcastill on 12/26/15.
//

#include <iostream>
#include "TestObject.h"

TestObject::TestObject()
{
    cout << "TestObject()" << endl;
}

TestObject::~TestObject()
{
    cout << "~TestObject()" << endl;
}

void TestObject::init()
{
    texture = loadTexture("stick.png");
    texture->unique(true);
}

void TestObject::render()
{
    int w = gfx->width() / 2 - texture->getWidth() / 2;
    int h = gfx->height() / 2 - texture->getHeight() / 2;
    gfx->renderTexture(texture, w, h);
}
