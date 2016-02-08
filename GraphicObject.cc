//

#include "GraphicObject.h"

#include <iostream>

// Created by rcastill on 12/18/15.

GraphicObject::GraphicObject() :
    objectEnabled(true),
    gfx(nullptr),
    layer(DEFAULT),
    initialized(false)
{
}

GraphicObject::~GraphicObject()
{
    cout << "~GraphicObject(";
    if (gfx) {
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


void GraphicObject::onMouseMotion(int x, int y)
{
}

void GraphicObject::continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState)
{
}

void GraphicObject::onQuit()
{
}

void GraphicObject::onKeyPressed(SDL_Keycode key)
{
}

void GraphicObject::onKeyReleased(SDL_Keycode key)
{
}

void GraphicObject::onMouseLeftPressed(int x, int y)
{
}

void GraphicObject::onMouseMiddlePressed(int x, int y)
{
}

void GraphicObject::onMouseRightPressed(int x, int y)
{
}

void GraphicObject::onMouseLeftReleased(int x, int y)
{
}

void GraphicObject::onMouseMiddleReleased(int x, int y)
{
}

void GraphicObject::onMouseRightReleased(int x, int y)
{
}

void GraphicObject::render(Renderer &renderer)
{
}

bool GraphicObject::enabled() const
{
    return objectEnabled;
}

void GraphicObject::enabled(bool objectEnabled)
{
    assert(gfx);
    gfx->cacheObjects();
    this->objectEnabled = objectEnabled;
}

void GraphicObject::unsetGraphicsEngine()
{
    gfx = nullptr;

    for (auto& child : children)
        child->unsetGraphicsEngine();
}

Texture *GraphicObject::loadTexture(string path)
{
    assert(gfx);
    Texture *texture = gfx->loadTexture(path);
    if (texture) resources.push_back(texture);
    return texture;
}

void GraphicObject::stop()
{
    assert(gfx);
    gfx->stop();
}

Font *GraphicObject::loadFont(string path, int size)
{
    assert(gfx);
    Font* font = gfx->loadFont(path, size);
    if (font) resources.push_back(font);
    return font;
}

Texture *GraphicObject::makeText(Font *font, string text, Color color, FontQuality quality, bool unique)
{
    assert(gfx);
    Texture* texture = gfx->makeText(font, text, color, quality, unique);
    if (texture) resources.push_back(texture);
    return texture;
}

void GraphicObject::windowTitle(string wTitle)
{
    assert(gfx);
    gfx->windowTitle(wTitle);
}

string GraphicObject::windowTitle() const
{
    assert(gfx);
    return gfx->windowTitle();
}

int GraphicObject::getFps() const
{
    assert(gfx);
    return gfx->getFps();
}

double GraphicObject::deltaTime() const
{
    assert(gfx);
    return gfx->deltaTime();
}

void GraphicObject::deltaTime(double delta)
{
    assert(gfx);
    gfx->deltaTime(delta);
}

int GraphicObject::screenWidth()
{
    assert(gfx);
    return gfx->width();
}

int GraphicObject::screenHeight()
{
    assert(gfx);
    return gfx->height();
}

void GraphicObject::screenSize(int &w, int &h)
{
    assert(gfx);
    gfx->size(w, h);
}

RenderLayer GraphicObject::renderLayer() const
{
    return layer;
}

void GraphicObject::renderLayer(RenderLayer layer)
{
    this->layer = layer;
}

void GraphicObject::initialize(GraphicsEngine *gfx)
{
    this->gfx = gfx;
    init();
    initialized = true;
}
