//
// Created by rcastill on 12/18/15.
//

#include "GraphicObject.h"
#include "GraphicsEngine.h"

#include <iostream>

GraphicObject::GraphicObject() :
        gfx(nullptr),
        objectEnabled(true)
{
    //cout << "GraphicObject()" << endl;
}

GraphicObject::~GraphicObject()
{
    cout << "~GraphicObject(";
    if (checkEngine()) {
        cout << "...";
        for (Resource *resource : resources)
            resource->dispose();

        cout << "dispose);" << endl;
        resources.clear();

    } else {
        cout << ");" << endl;
    }
}

void GraphicObject::init()
{
}

void GraphicObject::update(SDL_Event &event)
{
}

void GraphicObject::render()
{
}


bool GraphicObject::enabled() const
{
    return objectEnabled;
}

void GraphicObject::enabled(bool objectEnabled)
{
    this->objectEnabled = objectEnabled;
}

Texture *GraphicObject::loadTexture(string path)
{
    if (!checkEngine())
        return nullptr;

    Texture *texture = gfx->loadTexture(path);
    if (texture) resources.push_back(texture);
    return texture;
}

bool GraphicObject::checkEngine() const
{
    return gfx != nullptr;
}

void GraphicObject::unsetGraphicsEngine()
{
    gfx = nullptr;

    for (auto& child : children)
        child->unsetGraphicsEngine();
}
