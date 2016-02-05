//
// Created by rcastill on 12/26/15.
//

#include <iostream>
#include "TestObject.h"

TestObject::TestObject() :
    pos(400, 300)
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

void TestObject::render(Renderer &renderer)
{
    /*int x = screenWidth() / 2 - texture->getWidth() / 2;
    int y = screenHeight() / 2 - texture->getHeight() / 2;*/
    renderer.renderTexture(texture, pos);
    //renderTexture(texture, w, h);
}
