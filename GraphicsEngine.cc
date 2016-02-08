#include "GraphicsEngine.h"
#include "GraphicObject.h"

#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"

bool LayerComparison::operator()(const shared_ptr<GraphicObject> &lhs, const shared_ptr<GraphicObject> &rhs)
{
    return lhs->renderLayer() > rhs->renderLayer();
}

GraphicsEngine::GraphicsEngine(string title, int width, int height, double fps) :
    loadObjects(true),
    currentQueue(&objectQueue1),
    auxQueue(&objectQueue2),
    wTitle(title),
    windowWidth(width),
    windowHeight(height),
    running(true),
    delta(1 / fps),
    fps((int) fps)
{
    SDL_Window *tmpWindow = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_HIDDEN
    );

    if (tmpWindow == 0)
        throw runtime_error(SDL_GetError());

    sdlWindow.get_deleter() = [](SDL_Window *w) {
        SDL_DestroyWindow(w);
    };
    sdlWindow.reset(tmpWindow);

    SDL_Renderer *tmpRenderer = SDL_CreateRenderer(sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED);
    renderer = Renderer(tmpRenderer);

    if (tmpRenderer == 0)
        throw runtime_error(SDL_GetError());
}

GraphicsEngine::GraphicsEngine(int width, int height, double fps)
    : GraphicsEngine("", width, height, fps)
{
}

GraphicsEngine::~GraphicsEngine()
{
    for (auto &object : gfxObjects)
        object->unsetGraphicsEngine();

    cout << "~GraphicsEngine" << endl;
}


void GraphicsEngine::openWindow()
{
    SDL_ShowWindow(sdlWindow.get());
}

void GraphicsEngine::delay(int msecs)
{
    SDL_Delay((Uint32) msecs);
}

void GraphicsEngine::setRenderColor(Color color)
{
    SDL_SetRenderDrawColor(
            renderer,
            color.r(),
            color.g(),
            color.b(),
            color.a()
    );
}

void GraphicsEngine::windowTitle(string wTitle)
{
    this->wTitle = wTitle;
    SDL_SetWindowTitle(sdlWindow.get(), wTitle.c_str());
}

string GraphicsEngine::windowTitle() const
{
    return wTitle;
}

int GraphicsEngine::width() const
{
    return windowWidth;
}

int GraphicsEngine::height() const
{
    return windowHeight;
}

double GraphicsEngine::deltaTime() const
{
    return delta;
}

void GraphicsEngine::deltaTime(double delta)
{
    this->delta = delta;
}

void GraphicsEngine::doLevel(function<void(shared_ptr<GraphicObject> &)> callback,
                             bool load,
                             bool ignoreInitRestriction)
{
    if (load) {
        /* clear queue */
        while (!currentQueue->empty())
            currentQueue->pop();

        /* load root objects */
        for (auto obj : gfxObjects)
            currentQueue->push(obj);
    }

    while (!currentQueue->empty()) {
        auto object = currentQueue->top();
        auxQueue->push(object);
        currentQueue->pop();

        /* If not initialized */
        if (!object->initialized && !ignoreInitRestriction)
            continue;

        /* If not enabled */
        if (!object->enabled())
            continue;

        callback(object);

        if (load) {
            for (auto &child : object->children)
                currentQueue->push(child);
        }
    }

    /* Swap currentQueue with auxQueue */
    swapQueues();
}

void GraphicsEngine::swapQueues()
{
    ObjectQueue *tmp = currentQueue;
    currentQueue = auxQueue;
    auxQueue = tmp;
}

bool GraphicsEngine::shouldLoad()
{
    if (loadObjects) {
        loadObjects = false;
        return true;
    }

    return false;
}

void GraphicsEngine::triggerUpdateCallbacks()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        /* Update objects */
        //loadQueue();
        doLevel([&event](shared_ptr<GraphicObject> &obj)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        obj->onMouseLeftPressed(event.button.x, event.button.y);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        obj->onMouseMiddlePressed(event.button.x, event.button.y);
                        break;

                    case SDL_BUTTON_RIGHT:
                        obj->onMouseRightPressed(event.button.x, event.button.y);
                        break;
                }

            } else if (event.type == SDL_MOUSEBUTTONUP) {
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        obj->onMouseLeftReleased(event.button.x, event.button.y);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        obj->onMouseMiddleReleased(event.button.x, event.button.y);
                        break;

                    case SDL_BUTTON_RIGHT:
                        obj->onMouseRightReleased(event.button.x, event.button.y);
                        break;
                }

            } else if (event.type == SDL_MOUSEMOTION) {
                obj->onMouseMotion(event.motion.x, event.motion.y);

            } else if (event.type == SDL_KEYDOWN) {
                obj->onKeyPressed(event.key.keysym.sym);

            } else if (event.type == SDL_KEYUP) {
                obj->onKeyReleased(event.key.keysym.sym);

            } else if (event.type == SDL_QUIT) {
                obj->onQuit();
            }

        }, shouldLoad());
    }
}

void GraphicsEngine::triggerContinuousUpdate()
{
    /* Mouse continuous state */
    MouseState mouseState;
    Uint32 contButton;

    /* Get continuous state */
    contButton = SDL_GetMouseState(&mouseState.pos.x, &mouseState.pos.y);
    mouseState.leftPressed = (bool) (contButton & SDL_BUTTON(SDL_BUTTON_LEFT));
    mouseState.middlePressed = (bool) (contButton & SDL_BUTTON(SDL_BUTTON_MIDDLE));
    mouseState.rightPressed = (bool) (contButton & SDL_BUTTON(SDL_BUTTON_RIGHT));

    // Free update
    doLevel([&mouseState](shared_ptr<GraphicObject> &obj)
    {
        obj->continuousUpdate(SDL_GetKeyboardState(NULL), mouseState);

    }, shouldLoad());
}

int GraphicsEngine::getFps() const
{
    return fps;
}

void GraphicsEngine::mainloop()
{
    auto ticks2secs = []() -> double
    {
        return SDL_GetTicks() / 1000.0;
    };

    /* Should render? */
    bool render;

    /* Init objects */
    //loadQueue();
    doLevel([this](shared_ptr<GraphicObject> &obj)
    {
        obj->initialize(this);

    }, shouldLoad(), true);

    /* We most certainly have to reload */
    loadObjects = true;

    /* First children must not be initialized (again) */
    while (!initQueue.empty())
        initQueue.pop();

    /* Fixed delta time */
    //double delta = frameTime;

    /* Time variables */
    double currentTime = ticks2secs();
    double accumulator = 0.0;
    double newTime;
    double frameTime;

    /* Stats variables */
    double elapsed = 0;
    int frameCount = 0;

    while (running) { ;
        /* Reset */
        render = false;

        /* Get render frame lasting time */
        newTime = ticks2secs();
        frameTime = newTime - currentTime;
        currentTime = newTime;

        /* Increase accumulator and second counter */
        accumulator += frameTime;
        elapsed += frameTime;

        /* "spend" the accumulator time until is lower than the delta time.
        while we have time accumulated left, we trigger updates. */
        while (accumulator > delta) {
            render = true;

            /* Update Callbacks */
            triggerUpdateCallbacks();

            /* Continuous update */
            triggerContinuousUpdate();

            accumulator -= delta;
        }

        if (render) {
            SDL_RenderClear(renderer);

            renderer.enabled(true);
            //loadQueue();
            doLevel([this](shared_ptr<GraphicObject> &obj)
            {
                obj->render(renderer);

            }, shouldLoad());
            renderer.enabled(false);

            SDL_RenderPresent(renderer);

            /* One more frame in this second */
            frameCount++;

        } else {
            /* Optimization */
            SDL_Delay(1);
        }

        /* We have to reload objects */
        if (!initQueue.empty())
            loadObjects = true;

        /* Init late objects */
        while (!initQueue.empty()) {
            initQueue.top()->initialize(this);
            initQueue.pop();
        }

        if (elapsed >= 1) {
            fps = frameCount;
            elapsed = frameCount = 0;
        }
    }
}

void GraphicsEngine::disposeResource(Resource *resource)
{
    if (--(resource->refCount) == 0) {
        cout << availableResIds.empty() << endl;
        availableResIds.push_back(resource->id());
        resources[resource->id()] = 0;
    }
}

Texture *GraphicsEngine::loadTexture(string path)
{
    Resource *rawResource = checkResource(path);
    Texture *foundTexture = dynamic_cast<Texture*>(rawResource);

    if (foundTexture != NULL) {
        foundTexture->retain();
        return foundTexture;
    }

    SDL_Texture *sdlTexture = 0;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        return 0;

    sdlTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (sdlTexture == NULL)
        return 0;

    SDL_FreeSurface(loadedSurface);

    auto texture = makeTexture(path, sdlTexture);
    cacheResource(texture);

    return texture.get();
}

Font *GraphicsEngine::loadFont(string path, int size)
{
    string infoPath = "font://" + path + "/" + to_string(size);

    Resource *rawResource = checkResource(infoPath);
    Font *foundFont = dynamic_cast<Font*>(rawResource);

    if (foundFont != NULL)
        return foundFont;

    auto font = shared_ptr<Font>(new Font(path, size));

    if (!(font->ttfFont))
        return 0;

    /* Ugly but necessary: Replace path */
    font->path = infoPath;

    cacheResource(font);

    return font.get();
}

Texture *GraphicsEngine::makeText(Font *font, string text, Color color, FontQuality quality, bool unique)
{
    string path = "text://" + text;

    Resource *rawResource = checkResource(path);
    Texture *foundTexture = dynamic_cast<Texture*>(rawResource);

    if (foundTexture)
        return foundTexture;

    SDL_Surface *surface = NULL;

    if (quality == FQ_LOW)
        surface = TTF_RenderText_Solid(font->ttfFont.get(), text.c_str(), color.getSdlColor());
    else if (quality == FQ_MID)
        surface = TTF_RenderText_Shaded(font->ttfFont.get(), text.c_str(), color.getSdlColor(),
                                        color.negative().getSdlColor());
    else if (quality == FQ_HIGH)
        surface = TTF_RenderText_Blended(font->ttfFont.get(), text.c_str(), color.getSdlColor());
    else
        throw runtime_error("Invalid font quality");

    if (surface == NULL)
        return 0;

    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);

    if (sdlTexture == NULL)
        return 0;

    SDL_FreeSurface(surface);

    auto texture = makeTexture(path, sdlTexture);
    texture->unique(unique);
    cacheResource(texture);

    return texture.get();
}

void GraphicsEngine::size(int &w, int &h) const
{
    w = windowWidth;
    h = windowHeight;
}

Resource *GraphicsEngine::checkResource(string path)
{
    for (auto &resource : resources) {
        if (resource && resource->getPath() == path) {
            if (resource->unique())
                continue;

            return resource.get();
        }
    }

    return NULL;
}

void GraphicsEngine::cacheResource(shared_ptr<Resource> resource)
{
    if (!availableResIds.empty()) {
        resource->id(availableResIds.back());
        resources[availableResIds.back()] = resource;
        availableResIds.pop_back();

    } else {
        resource->id(resources.size());
        resources.push_back(resource);
    }

    resource->gfx = this;
}

shared_ptr<Texture> GraphicsEngine::makeTexture(string path, SDL_Texture *raw)
{
    auto texture = make_shared<Texture>(path);
    texture->sdlTexture = raw;
    texture->updateInfo();
    return texture;
}

void GraphicsEngine::stop()
{
    running = false;
}

void GraphicsEngine::cacheObjects()
{
    loadObjects = true;
}

void GraphicsEngine::addToInitQueue(const shared_ptr<GraphicObject> &object)
{
    initQueue.push(object);
}

GraphicsEngine::SDL2Systems::SDL2Systems()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw runtime_error(IMG_GetError());

    if (TTF_Init() < 0)
        throw runtime_error(TTF_GetError());
}

GraphicsEngine::SDL2Systems::~SDL2Systems()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

#pragma clang diagnostic pop
